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


    qint64 totalBytes;  //����ܴ�С��Ϣ
    qint64 m_bytesReceived;  //���յ����ݵĴ�С
    qint64 fileNameSize;  //�ļ����Ĵ�С��Ϣ
    QString fileName;   //����ļ���
    QFile *localFile;   //�����ļ�
    QByteArray inBlock;   //���ݻ�����
};

#endif // MAINWINDOW_H
