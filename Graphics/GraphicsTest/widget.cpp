#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 定义一个场景，是用以管理图元项的容器
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::gray);

    QPen pen;
    pen.setColor(QColor(0, 160, 230));
    pen.setWidth(10);

    // 定义一个矩形图元
    QGraphicsRectItem *rectItem = new QGraphicsRectItem();
    rectItem->setRect(0, 0, 80, 80);
    rectItem->setPen(pen);
    rectItem->setBrush(QBrush(QColor(255, 0, 255)));
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(rectItem);

    // 定义一个直线图元
    QGraphicsLineItem *lineItem = new QGraphicsLineItem();
    lineItem->setLine(QLineF(0, 0, 100, 100));
    lineItem->setPen(pen);
    lineItem->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(lineItem);

    // 定义一个路径图元
    QGraphicsPathItem *pathItem = new QGraphicsPathItem();
    QPainterPath path;
    path.moveTo(90, 50);
    for(int i = 1; i < 5; ++i)
        path.lineTo(50 + 40 * cos(0.8 * i * M_PI), 50 + 40 * sin(0.8 * i * M_PI));
    path.closeSubpath();
    pathItem->setPath(path);
    pathItem->setPen(pen);
    pathItem->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(pathItem);

    // 定义一个多边形图元
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem();
    QPolygonF polygon;
    polygon << QPointF(-100.0, -150.0) << QPointF(-120.0, 150.0) << QPointF(320.0, 160.0) << QPointF(220.0, -140.0);
    polygonItem->setPolygon(polygon);
    polygonItem->setPen(pen);
    polygonItem->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(polygonItem);

    QVBoxLayout *main_layout = new QVBoxLayout();
    // 定义一个视图，用于显示场景中的内容
    QGraphicsView *view = new QGraphicsView(scene);
    main_layout->addWidget(view);
    this->setLayout(main_layout);
}

Widget::~Widget()
{
    delete ui;
}
