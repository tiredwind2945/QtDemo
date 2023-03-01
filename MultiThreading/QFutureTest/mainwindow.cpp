#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QStandardPaths>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrentMap>
#include <QBoxLayout>
#include <QDebug>
#include <qmath.h>

const int c_nImageSize = 100;

// 缩放图片
QImage scale(const QString &imageFileName)
{
    QImage image(imageFileName);
    return image.scaled(QSize(c_nImageSize, c_nImageSize), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initInterface();
}

MainWindow::~MainWindow()
{
    watcher->cancel();
    watcher->waitForFinished();
    delete ui;
}

void MainWindow::initInterface()
{
    watcher = new QFutureWatcher<QImage>(this);
    btn_open = new QPushButton(QStringLiteral("打开图片"));
    btn_cancel = new QPushButton(QStringLiteral("取消"));
    btn_pause = new QPushButton(QStringLiteral("暂停/恢复"));
    QProgressBar *pProgressBar = new QProgressBar(this);

    btn_cancel->setEnabled(false);
    btn_pause->setEnabled(false);

    // 布局
    QHBoxLayout *pButtonLayout = new QHBoxLayout();
    pButtonLayout->addWidget(btn_open);
    pButtonLayout->addWidget(btn_cancel);
    pButtonLayout->addWidget(btn_pause);
    pButtonLayout->addStretch();
    pButtonLayout->setSpacing(10);
    pButtonLayout->setMargin(0);

    m_pImagesLayout = new QGridLayout();

    QVBoxLayout *m_pMainLayout = new QVBoxLayout();
    m_pMainLayout->addLayout(pButtonLayout);
    m_pMainLayout->addWidget(pProgressBar);
    m_pMainLayout->addLayout(m_pImagesLayout);
    m_pMainLayout->addStretch();
    m_pMainLayout->setSpacing(10);
    m_pMainLayout->setContentsMargins(10, 10, 10, 10);
    this->centralWidget()->setLayout(m_pMainLayout);

    connect(watcher, &QFutureWatcherBase::resultReadyAt, this, &MainWindow::showImage);
    connect(watcher, &QFutureWatcherBase::progressRangeChanged, pProgressBar, &QProgressBar::setRange);
    connect(watcher, &QFutureWatcherBase::progressValueChanged, pProgressBar, &QProgressBar::setValue);
    connect(watcher, &QFutureWatcherBase::finished, this, &MainWindow::finished);
    connect(btn_open, SIGNAL(clicked()), SLOT(open()));
    connect(btn_cancel, SIGNAL(clicked()), watcher, SLOT(cancel()));
    connect(btn_pause, SIGNAL(clicked()), watcher, SLOT(togglePaused()));
}

void MainWindow::open()
{
    // 如果已经加载图片，取消并进行等待
    if(watcher->isRunning())
    {
        watcher->cancel();
        watcher->waitForFinished();
    }

    // 显示一个文件打开对话框
    QStringList files = QFileDialog::getOpenFileNames(this, QStringLiteral("选择图片"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "*.jpg *.png");
    if (files.count() == 0)
        return;

    // 做一个简单的布局
    qDeleteAll(labels);
    labels.clear();

    int dim = qSqrt(qreal(files.count())) + 1;
    for(int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            QLabel *pLabel = new QLabel(this);
            pLabel->setFixedSize(c_nImageSize, c_nImageSize);
            m_pImagesLayout->addWidget(pLabel, i, j);
            labels.append(pLabel);
        }
    }

    // 使用 mapped 来为 files 运行线程安全的 scale 函数
    watcher->setFuture(QtConcurrent::mapped(files, scale));

    btn_open->setEnabled(false);
    btn_cancel->setEnabled(true);
    btn_pause->setEnabled(true);
}

void MainWindow::showImage(int index)
{
    labels[index]->setPixmap(QPixmap::fromImage(watcher->resultAt(index)));
}

void MainWindow::finished()
{
    btn_open->setEnabled(true);
    btn_cancel->setEnabled(false);
    btn_pause->setEnabled(false);
}
