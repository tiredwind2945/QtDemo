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

    QPointer<QFile> localFile;  //Ҫ���͵��ļ�
    qint64 totalBytes;  //�����ܴ�С
    qint64 bytesWritten;  //�Ѿ��������ݴ�С
    qint64 bytesToWrite;   //ʣ�����ݴ�С
    qint64 loadSize;   //ÿ�η������ݵĴ�С
    QString fileName;  //�����ļ�·��
    QByteArray outBlock;  //���ݻ������������ÿ��Ҫ���͵�����
};

#endif // MAINWINDOW_H
