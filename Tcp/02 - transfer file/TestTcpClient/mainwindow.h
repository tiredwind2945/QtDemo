#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class MainWindow;
}
class QTcpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slot_update_progress(qint64 numBytes);
    void slot_display_error(QAbstractSocket::SocketError);
    void slot_start_transfer();

    void on_btn_sendfile_clicked();
    void on_btn_choosefile_clicked();

private:
    Ui::MainWindow *ui;

    QPointer<QTcpSocket> m_socket;

    QPointer<QFile> localFile;  //要发送的文件
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    QString fileName;  //保存文件路径
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据
};

#endif // MAINWINDOW_H
