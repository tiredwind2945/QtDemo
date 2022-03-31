#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

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
    void slot_readmsg();

    void on_btn_send_clicked();

private:
    Ui::MainWindow *ui;

    QPointer<QTcpServer> m_server;
    QPointer<QTcpSocket> m_socket;
};

#endif // MAINWINDOW_H
