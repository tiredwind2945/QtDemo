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

    qint64 m_total_bytes;           // total size of file
    qint64 m_bytes_received;        // size of received file
    qint64 m_filename_size;         // size of file's name
    QString m_filename;
    QPointer<QFile> m_localfile;    // recevied file
    QByteArray m_inblock;           // data buffer
};

#endif // MAINWINDOW_H
