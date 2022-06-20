#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPointer>

#include <vtkNew.h>
#include <vtkSmartPointer.h>

class QVTKOpenGLNativeWidget;
class vtkRenderer;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void viewDirection(vtkRenderer* renderer, double lookX, double lookY, double lookZ, double upX, double upY, double upZ);


private slots:
    void on_btn_front_clicked();
    void on_btn_back_clicked();
    void on_btn_left_clicked();
    void on_btn_right_clicked();
    void on_btn_top_clicked();
    void on_btn_bottom_clicked();

private:
    Ui::Widget *ui;

    QPointer<QVTKOpenGLNativeWidget> vtk_widget;
    vtkSmartPointer<vtkRenderer> renderer;
};

#endif // WIDGET_H
