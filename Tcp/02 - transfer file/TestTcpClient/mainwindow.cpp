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
    //�Ѿ��������ݵĴ�С
    bytesWritten += (int)numBytes;

    if(bytesToWrite > 0) //����Ѿ�����������
    {
        // ÿ�η���loadSize��С�����ݣ���������Ϊ4KB�����ʣ������ݲ���4KB��
        // �ͷ���ʣ�����ݵĴ�С
        outBlock = localFile->read(qMin(bytesToWrite,loadSize));

        // ������һ�����ݺ�ʣ�����ݵĴ�С
        bytesToWrite -= (int)m_socket->write(outBlock);

        // ��շ��ͻ�����
        outBlock.resize(0);
        }
    else    localFile->close(); //���û�з����κ����ݣ���ر��ļ�

    // ���½�����
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWritten);

    if(bytesWritten == totalBytes) //�������
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

    // ����д���ܴ�С��Ϣ�ռ䣬�ļ�����С��Ϣ�ռ䣬�ļ���
    sendOut << qint64(0) << qint64(0) << currentFileName;

    // ������ܴ�С���ļ�����С����Ϣ��ʵ���ļ���С���ܺ�
    totalBytes += outBlock.size();

    sendOut.device()->seek(0);
    // ��outBolock�Ŀ�ʼ����ʵ�ʵĴ�С��Ϣ��������qint64(0)�ռ�
    sendOut<<totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));

    // ������ͷ���ݺ�ʣ�����ݵĴ�С
    bytesToWrite = totalBytes - m_socket->write(outBlock);

    ui->txb_msg->append(tr("Connected!\n"));
    outBlock.resize(0);
}

void MainWindow::on_btn_sendfile_clicked()
{
    ui->btn_sendfile->setEnabled(false);
    bytesWritten = 0;
    // ��ʼ���ѷ����ֽ�Ϊ0
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
