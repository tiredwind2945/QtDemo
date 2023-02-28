#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPointer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
class QSqlQuery;
class QSqlTableModel;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QPointer<QSqlTableModel> tbv_model;
    // QPointer<QSqlQuery> sql_query;
};
#endif // WIDGET_H
