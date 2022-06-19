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
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renWin;

    renderer->SetBackground2(colors->GetColor3d("Silver").GetData());
    renderer->SetBackground(colors->GetColor3d("Gold").GetData());
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
        vtkActor* actor = actors->GetNextActor();
        if(actor->GetTexture())    actor->GetTexture()->InterpolateOn();

        vtkPolyData* pd = dynamic_cast<vtkPolyData*>(actor->GetMapper()->GetInput());
        vtkPolyDataMapper* mapper = dynamic_cast<vtkPolyDataMapper*>(actor->GetMapper());
        mapper->SetInputData(pd);
    }

    vtk_widget = new QVTKOpenGLNativeWidget();
    vtk_widget->setRenderWindow(renWin);
    vtk_widget->renderWindow()->Render();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(vtk_widget);
    this->setLayout(main_layout);
}

Widget::~Widget()
{
    delete ui;
}
