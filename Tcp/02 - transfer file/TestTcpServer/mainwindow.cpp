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

    totalBytes = 0;
    m_bytesReceived = 0;
    fileNameSize = 0;
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
    ui->txb_msg->append("Start receiving files...\n");

    m_server->close();
}

void MainWindow::slot_update_progress()
{
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_4_8);
    if(m_bytesReceived <= sizeof(qint64) * 2)
    {
        // 如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息
        if((m_socket->bytesAvailable() >= sizeof(qint64) * 2) && (fileNameSize == 0))
        {
            // 接收数据总大小信息和文件名大小信息
            in >> totalBytes >> fileNameSize;
            m_bytesReceived += sizeof(qint64) * 2;
        }
        if((m_socket->bytesAvailable() >= fileNameSize) && (fileNameSize != 0))
        {
            // 接收文件名，并建立文件
            in >> fileName;
            ui->txb_msg->append(tr("Receicing file %1 ...\n").arg(fileName));
            m_bytesReceived += fileNameSize;
            localFile= new QFile(fileName);
            if(!localFile->open(QFile::WriteOnly))
            {
               qDebug() << "open file error!";
               return;
            }
        }
        else return;
    }

    if(m_bytesReceived < totalBytes)
    {
        // 如果接收的数据小于总数据，那么写入文件
        m_bytesReceived += m_socket->bytesAvailable();
        inBlock = m_socket->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    // update progressbar
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(m_bytesReceived);

    if(m_bytesReceived == totalBytes)
    {
        // 接收数据完成时
        m_socket->close();
        localFile->close();
        ui->btn_start->setEnabled(true);
        ui->txb_msg->append(tr("Received file %1 successful!\n").arg(fileName));
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
    m_bytesReceived = 0;
    if(!m_server->listen(QHostAddress::LocalHost, 9091))
    {
        QString error_str = "ERROR: " + m_server->errorString();
        ui->txb_msg->append(error_str + "\n");
        close();
        return;
    }
    ui->txb_msg->append("Start listening...\n");
}
