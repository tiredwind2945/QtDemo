#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QPointer>
#include <QFile>

namespace Ui {
class MainWindow;
}
class QTcpServer;
class QTcpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = NULL);
    ~MainWindow();

private slots:
    void slot_new_tcpconnect();
    void slot_update_progress();
    void slot_display_error(QAbstractSocket::SocketError);

    void on_btn_start_clicked();

private:
    Ui::MainWindow *ui;

    QPointer<QTcpServer> m_server;
    QPointer<QTcpSocket> m_socket;


    qint64 totalBytes;  //存放总大小信息
    qint64 m_bytesReceived;  //已收到数据的大小
    qint64 fileNameSize;  //文件名的大小信息
    QString fileName;   //存放文件名
    QFile *localFile;   //本地文件
    QByteArray inBlock;   //数据缓冲区
};

#endif // MAINWINDOW_H
