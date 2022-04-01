#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_server = new QTcpServer(this);
    if(!m_server->listen(QHostAddress::LocalHost, 9091))
    {
        QString error = m_server->errorString();
        qDebug() << "error:" << error << endl;
        close();
    }
    else qDebug() << "Tcp Server is listening...";

    connect(m_server, SIGNAL(newConnection()), this, SLOT(slot_new_tcpconnect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_new_tcpconnect()
{
    qDebug() << "server has connected!" << endl;
    m_socket = m_server->nextPendingConnection();
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(slot_readmsg()));
    // connect(m_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

void MainWindow::slot_readmsg()
{
    ui->txb_msg->append(m_socket->readAll());
}

void MainWindow::on_btn_send_clicked()
{
    m_socket->write("server button has clieked!", 1024);
}
