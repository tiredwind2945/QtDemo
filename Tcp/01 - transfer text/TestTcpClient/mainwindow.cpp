#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_socket = new QTcpSocket(this);
    m_socket->abort();  // disconnect the previous connection
    m_socket->connectToHost(QHostAddress::LocalHost, 9091);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(slot_readmsg()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_display_error(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_readmsg()
{
    ui->txb_msg->append(m_socket->readAll());
}

void MainWindow::slot_display_error(QAbstractSocket::SocketError )
{
    qDebug() << "ERROR: " << m_socket->errorString();
}

void MainWindow::on_btn_send_clicked()
{
    m_socket->write("client button has clicked!", 1024);
}
