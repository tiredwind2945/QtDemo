#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPointer>

class QVTKOpenGLNativeWidget;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QPointer<QVTKOpenGLNativeWidget> vtk_widget;
};

#endif // WIDGET_H
