#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_load_size = 4 * 1024;
    m_total_bytes = 0;
    m_written_bytes = 0;
    m_towrite_bytes = 0;

    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(connected()), this, SLOT(slot_start_transfer()));
    connect(m_socket, SIGNAL(bytesWritten(qint64)),this, SLOT(slot_update_progress(qint64)));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_display_error(QAbstractSocket::SocketError)));
    ui->btn_sendfile->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_update_progress(qint64 numBytes)
{
    m_written_bytes += (int)numBytes;

    if(m_towrite_bytes > 0)
    {
        // size of send file is m_load_size each time
        m_outblock = m_localfile->read(qMin(m_towrite_bytes, m_load_size));
        m_towrite_bytes -= (int)m_socket->write(m_outblock);
        m_outblock.resize(0);
    }
    else    m_localfile->close();

    ui->progressBar->setMaximum(m_total_bytes);
    ui->progressBar->setValue(m_written_bytes);

    if(m_written_bytes == m_total_bytes)
    {
        ui->txb_msg->setText(tr("Send file %1 successful!\n").arg(m_filename));
        m_localfile->close();
        m_socket->close();
    }
}

void MainWindow::slot_display_error(QAbstractSocket::SocketError )
{
    QString error_str = "ERROR: " + m_socket->errorString();
    qDebug() << error_str;
    ui->txb_msg->append(error_str + "\n");
    m_socket->close();
    ui->progressBar->reset();
    ui->btn_sendfile->setEnabled(true);
}

void MainWindow::slot_start_transfer()
{
    m_localfile = new QFile(m_filename);
    if(!m_localfile->open(QFile::ReadOnly))
    {
       qDebug() << "open file error!" << endl;
       ui->txb_msg->append("open file error!\n");
       return;
    }

    m_total_bytes = m_localfile->size();

    QDataStream sendOut(&m_outblock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_8);
    QString currentm_filename = m_filename.right(m_filename.size() - m_filename.lastIndexOf('/') - 1);

    // write the total size information, the file name size information, and the filename in turn
    sendOut << qint64(0) << qint64(0) << currentm_filename;
    m_total_bytes += m_outblock.size();

    sendOut.device()->seek(0);
    sendOut << m_total_bytes << qint64((m_outblock.size() - sizeof(qint64) * 2));
    m_towrite_bytes = m_total_bytes - m_socket->write(m_outblock);

    ui->txb_msg->append(tr("Connected!\n"));
    m_outblock.resize(0);
}

void MainWindow::on_btn_sendfile_clicked()
{
    ui->btn_sendfile->setEnabled(false);
    m_written_bytes = 0;

    ui->txb_msg->append(tr("Connecting...\n"));
    m_socket->connectToHost(QHostAddress::LocalHost, 9091);
}

void MainWindow::on_btn_choosefile_clicked()
{
    m_filename = QFileDialog::getOpenFileName(this);
    if(!m_filename.isEmpty())
    {
       ui->btn_sendfile->setEnabled(true);
       ui->txb_msg->append(tr("Open file %1 successful!\n").arg(m_filename));
    }
}
