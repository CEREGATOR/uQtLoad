#ifndef COMPONENTPAGE_H
#define COMPONENTPAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QNetworkProxy>

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
        QUrl url;
    }Qt_components;

    typedef struct
    {
        QStandardItem* name_qt;
        QStandardItem* vers_qt;

        QVector<Qt_components>* components;
    }Qt_;

public:
    explicit ComponentPage(QWidget *parent = nullptr);
    ~ComponentPage();

public slots:
    void getHTML(QStringList list);

signals:
    void s_nextPage();
    void s_prevPage();
    void s_setUrls(QVector<QUrl> urls);

private slots:
    void saveUrls();
    void treeItem_CheckChildChanged ( QStandardItem * item );
    void treeItemChanged ( QStandardItem * item );
    void treeItem_checkAllChild(QStandardItem * item, bool check);
    void treeItem_checkAllChild_recursion(QStandardItem * item,bool check);
    Qt::CheckState checkSibling(QStandardItem * item);
    void pageHTML(QNetworkReply *reply);

private:
    QVector<Qt_> all_qt;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    Ui::ComponentPage *ui;
};

#endif // COMPONENTPAGE_H
