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

    QPointer<QFile> m_localfile;    // file to send
    qint64 m_total_bytes;           // total size of file
    qint64 m_written_bytes;         // size of file that has been sent
    qint64 m_towrite_bytes;         // size of remaining file
    qint64 m_load_size;             // data size of sending each time
    QString m_filename;             // filepath(filename) of send file
    QByteArray m_outblock;          // data buffer
};

#endif // MAINWINDOW_H
