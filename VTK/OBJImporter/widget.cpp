#include "widget.h"
#include "ui_widget.h"

#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QDebug>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkOBJImporter.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkTexture.h>

//#include "vtkAutoInit.h"
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
//VTK_MODULE_INIT(vtkRenderingFreeType);


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkGenericOpenGLRenderWindow> renWin;

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.6, 0.6, 0.6);
    renderer->SetBackground2(0.9, 0.9, 0.9);
    renderer->GradientBackgroundOn();
    renWin->AddRenderer(renderer);
    renderer->UseHiddenLineRemovalOn();

    vtkNew<vtkOBJImporter> importer;
    importer->SetFileName("2guizi_01.obj");
    importer->SetFileNameMTL("2guizi_01.mtl");
    importer->SetRenderWindow(renWin);
    importer->Update();

    auto actors = renderer->GetActors();
    actors->InitTraversal();
    // qDebug() << "There are " << actors->GetNumberOfItems() << " actors";
    for(vtkIdType a = 0; a < actors->GetNumberOfItems(); ++a)
    {
        vtkActor *actor = actors->GetNextActor();
        if(actor->GetTexture())
        {
            actor->GetTexture()->InterpolateOn();
            actor->GetProperty()->BackfaceCullingOn();
        }

        vtkPolyData *pd = dynamic_cast<vtkPolyData*>(actor->GetMapper()->GetInput());
        vtkPolyDataMapper *mapper = dynamic_cast<vtkPolyDataMapper*>(actor->GetMapper());
        mapper->SetInputData(pd);
    }

    vtk_widget = new QVTKOpenGLNativeWidget();
    vtk_widget->setRenderWindow(renWin);
    vtk_widget->renderWindow()->Render();

    QVBoxLayout *main_layout = dynamic_cast<QVBoxLayout *>(this->layout());
    main_layout->addWidget(vtk_widget);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::viewDirection(vtkRenderer *renderer, double lookX, double lookY, double lookZ, double upX, double upY, double upZ)
{
    renderer->GetActiveCamera()->SetPosition(lookX, lookY, lookZ);    // 相机位置
    renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);			  // 焦点位置
    renderer->GetActiveCamera()->SetViewUp(upX, upY, upZ);			  // 相机朝上方向
    renderer->ResetCamera();
//    renderer->Render();
    vtk_widget->renderWindow()->Render();
}

void Widget::on_btn_front_clicked()
{
    this->viewDirection(renderer, 0, 0, 1, 0, 1, 0);
}

void Widget::on_btn_back_clicked()
{
    this->viewDirection(renderer, 0, 0, -1, 0, 1, 0);
}

void Widget::on_btn_left_clicked()
{
    this->viewDirection(renderer, -1, 0, 0, 0, 1, 0);
}

void Widget::on_btn_right_clicked()
{
    this->viewDirection(renderer, 1, 0, 0, 0, 1, 0);
}

void Widget::on_btn_top_clicked()
{
    this->viewDirection(renderer, 0, 1, 0, 0, 0, -1);
}

void Widget::on_btn_bottom_clicked()
{
    this->viewDirection(renderer, 0, -1, 0, 0, 0, 1);
}
