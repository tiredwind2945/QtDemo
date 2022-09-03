#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // print some query result
    QSqlQuery query("SELECT * FROM Test.user");
    while(query.next())
    {
        qDebug() << query.value("id").toString();
        qDebug() << query.value("username").toString();
        qDebug() << query.value("email").toString() << Qt::endl;
    }

    // construct tablemodel
    tbv_model = new QSqlTableModel(ui->tableView);
    tbv_model->setTable("user");
    tbv_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tbv_model->select();

    tbv_model->setHeaderData(0, Qt::Horizontal, tr("id"));
    tbv_model->setHeaderData(1, Qt::Horizontal, tr("username"));
    tbv_model->setHeaderData(2, Qt::Horizontal, tr("password"));
    tbv_model->setHeaderData(3, Qt::Horizontal, tr("email"));
    tbv_model->setHeaderData(4, Qt::Horizontal, tr("create_time"));

    ui->tableView->setModel(tbv_model);
    ui->tableView->resizeColumnsToContents();
}

Widget::~Widget()
{
    delete ui;
}

