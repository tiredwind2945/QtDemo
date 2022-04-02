#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpServer>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_server = new QTcpServer(this);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(slot_new_tcpconnect()));

    m_total_bytes = 0;
    m_bytes_received = 0;
    m_filename_size = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_new_tcpconnect()
{
    m_socket = m_server->nextPendingConnection();
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(slot_update_progress()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_display_error(QAbstractSocket::SocketError)));
    ui->txb_msg->append("Start receiving file...\n");

    m_server->close();
}

void MainWindow::slot_update_progress()
{
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_4_8);

    // start receiving data
    if(m_bytes_received <= sizeof(qint64) * 2)
    {
        if((m_socket->bytesAvailable() >= sizeof(qint64) * 2) && (m_filename_size == 0))
        {
            in >> m_total_bytes >> m_filename_size;
            m_bytes_received += sizeof(qint64) * 2;
        }
        if((m_socket->bytesAvailable() >= m_filename_size) && (m_filename_size != 0))
        {
            // write filename and create local file
            in >> m_filename;
            ui->txb_msg->append(tr("Receicing file %1 ...\n").arg(m_filename));
            m_bytes_received += m_filename_size;
            m_localfile = new QFile(m_filename);
            if(!m_localfile->open(QFile::WriteOnly))
            {
               qDebug() << "open file error!";
               return;
            }
        }
        else return;
    }

    if(m_bytes_received < m_total_bytes)
    {
        // writring file
        m_bytes_received += m_socket->bytesAvailable();
        m_inblock = m_socket->readAll();
        m_localfile->write(m_inblock);
        m_inblock.resize(0);
    }
    ui->progressBar->setMaximum(m_total_bytes);
    ui->progressBar->setValue(m_bytes_received);

    if(m_bytes_received == m_total_bytes)
    {
        // writing complete
        m_socket->close();
        m_localfile->close();
        ui->btn_start->setEnabled(true);
        ui->txb_msg->append(tr("Received file %1 successful!\n").arg(m_filename));
    }
}

void MainWindow::slot_display_error(QAbstractSocket::SocketError)
{
    QString error_str = "EERROR: " + m_socket->errorString();
    qDebug() << error_str;
    ui->txb_msg->append(error_str + "\n");

    m_server->close();
    ui->progressBar->reset();
    ui->btn_start->setEnabled(true);
}

void MainWindow::on_btn_start_clicked()
{
    ui->btn_start->setEnabled(false);
    m_bytes_received = 0;
    if(!m_server->listen(QHostAddress::LocalHost, 9091))
    {
        QString error_str = "ERROR: " + m_server->errorString();
        ui->txb_msg->append(error_str + "\n");

        close();
        return;
    }
    ui->txb_msg->append("Start listening...\n");
}
