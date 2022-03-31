#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

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
    void slot_readmsg();

    void on_btn_send_clicked();

private:
    Ui::MainWindow *ui;

    QPointer<QTcpSocket> m_socket;
};

#endif // MAINWINDOW_H
