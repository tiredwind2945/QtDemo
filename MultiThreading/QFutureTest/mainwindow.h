#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFuture>
#include <QFutureWatcher>
class QPushButton;
class QLabel;
class QImage;
class QGridLayout;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initInterface();

private slots:
    void open();                    // 打开目录，加载图片
    void showImage(int index);      // 显示图片
    void finished();                // 更新按钮状态

private:
    Ui::MainWindow *ui;

    QGridLayout *m_pImagesLayout;
    QPushButton *btn_open;
    QPushButton *btn_cancel;
    QPushButton *btn_pause;
    QList<QLabel *> labels;
    QFutureWatcher<QImage> *watcher;
};

#endif // MAINWINDOW_H
