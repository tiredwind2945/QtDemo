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

    loadSize = 4*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;

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
    //已经发送数据的大小
    bytesWritten += (int)numBytes;

    if(bytesToWrite > 0) //如果已经发送了数据
    {
        // 每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
        // 就发送剩余数据的大小
        outBlock = localFile->read(qMin(bytesToWrite,loadSize));

        // 发送完一次数据后还剩余数据的大小
        bytesToWrite -= (int)m_socket->write(outBlock);

        // 清空发送缓冲区
        outBlock.resize(0);
        }
    else    localFile->close(); //如果没有发送任何数据，则关闭文件

    // 更新进度条
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWritten);

    if(bytesWritten == totalBytes) //发送完毕
    {
        ui->txb_msg->setText(tr("Send file %1 successful!\n").arg(fileName));
        localFile->close();
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
    localFile = new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly))
    {
       qDebug() << "open file error!" << endl;
       ui->txb_msg->append("open file error!\n");
       return;
    }

    totalBytes = localFile->size();

    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_8);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);

    // 依次写入总大小信息空间，文件名大小信息空间，文件名
    sendOut << qint64(0) << qint64(0) << currentFileName;

    // 这里的总大小是文件名大小等信息和实际文件大小的总和
    totalBytes += outBlock.size();

    sendOut.device()->seek(0);
    // 回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    sendOut<<totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));

    // 发送完头数据后剩余数据的大小
    bytesToWrite = totalBytes - m_socket->write(outBlock);

    ui->txb_msg->append(tr("Connected!\n"));
    outBlock.resize(0);
}

void MainWindow::on_btn_sendfile_clicked()
{
    ui->btn_sendfile->setEnabled(false);
    bytesWritten = 0;
    // 初始化已发送字节为0
    ui->txb_msg->append(tr("Connecting...\n"));
    m_socket->connectToHost(QHostAddress::LocalHost, 9091);
}

void MainWindow::on_btn_choosefile_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
       ui->btn_sendfile->setEnabled(true);
       ui->txb_msg->append(tr("Open file %1 successful!\n").arg(fileName));
    }
}
