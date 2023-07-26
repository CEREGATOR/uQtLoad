#ifndef COMPONENTPAGE_H
#define COMPONENTPAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class ComponentPage;
}

class ComponentPage : public QWidget
{
    Q_OBJECT

    typedef struct
    {
        QStandardItem* name_com;
        QStandardItem* vers_com;
    }Qt_components;

    typedef struct
    {
        QStandardItem* name_qt;
        QStandardItem* vers_qt;

        QVector<Qt_components> components;

    }Qt_;

public:
    explicit ComponentPage(QWidget *parent = nullptr);
    ~ComponentPage();

signals:
    void s_nextPage();
    void s_prevPage();

private slots:
    void treeItem_CheckChildChanged ( QStandardItem * item );
    void treeItemChanged ( QStandardItem * item );
    void treeItem_checkAllChild(QStandardItem * item, bool check);
    void treeItem_checkAllChild_recursion(QStandardItem * item,bool check);
    Qt::CheckState checkSibling(QStandardItem * item);

private:
    Ui::ComponentPage *ui;
};

#endif // COMPONENTPAGE_H
