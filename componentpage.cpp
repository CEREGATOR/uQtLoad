#include "componentpage.h"
#include "ui_componentpage.h"
#include <QTranslator>

ComponentPage::ComponentPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentPage)
{
    ui->setupUi(this);

    QStandardItemModel* model = new QStandardItemModel(ui->treeView);

    model->setHorizontalHeaderLabels(QStringList()<<tr("Component Name")<<tr("Version"));

    connect ( model ,&QStandardItemModel::itemChanged , this ,&ComponentPage::treeItemChanged );

    ui->treeView->setModel(model);

    //    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&ComponentPage::s_nextPage);
    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&ComponentPage::s_prevPage);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&ComponentPage::saveUrls);

    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,this, &ComponentPage::pageHTML);
}

void ComponentPage::getHTML(QStringList list)
{
    QNetworkRequest request;
    QString url = list.at(0);
    request.setUrl(QUrl(url));
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    manager->get(request);
}

void ComponentPage::pageHTML(QNetworkReply *reply)
{
    QString buff = reply->readAll();
    QStringList listHref;
    QRegExp hrefRegExp("<a href=\"([^\"]+\\/)\"");

    int lastPos = 0;
    while ((lastPos = hrefRegExp.indexIn(buff, lastPos)) != -1) {
        lastPos += hrefRegExp.matchedLength();
        //        qDebug() << hrefRegExp.cap(1);
        listHref.push_back(hrefRegExp.cap(1));
    }
    listHref.removeDuplicates();

//    QRegExp versRegExp("(\\d+\\.\\d+\\.\\d+)\\-(\\d+)\\-(\\d+)(\\w+)");
//    foreach( QString str, listHref ) {
//        qDebug() << str;
//        lastPos = 0;
//        while ((lastPos = versRegExp.indexIn(str, lastPos)) != -1) {
//            lastPos += versRegExp.matchedLength();
//            //        qDebug() << versRegExp.cap(0);
//            qDebug() << versRegExp.cap(1); // version
//            qDebug() << versRegExp.cap(2);
//            qDebug() << versRegExp.cap(3); // date
//            qDebug() << versRegExp.cap(4); //name tool
//            //        listHref.push_back(versRegExp.cap(1));
//        }
//    }

}

void ComponentPage::saveUrls()
{
    QVector<QUrl> urls;
    for(Qt_ qt : all_qt)
    {
        for(size_t i = 0;i < qt.components->size();i++)
        {
            if(qt.components->at(i).name_com->checkState() == Qt::Checked)
            {
                urls.push_back(qt.components->at(i).url);
            }
        }
    }
    emit s_setUrls(urls);

    emit s_nextPage();
}

Qt::CheckState ComponentPage::checkSibling(QStandardItem * item)
{
    // Сначала получаем родственный узел через родительский узел
    QStandardItem * parent = item->parent();
    if(nullptr == parent)
        return item->checkState();
    int brotherCount = parent->rowCount();
    int checkedCount(0),unCheckedCount(0);
    Qt::CheckState state;
    for(int i=0;i<brotherCount;++i)
    {
        QStandardItem* siblingItem = parent->child(i);
        state = siblingItem->checkState();
        if(Qt::PartiallyChecked == state)
            return Qt::PartiallyChecked;
        else if(Qt::Unchecked == state)
            ++unCheckedCount;
        else
            ++checkedCount;
        if(checkedCount>0 && unCheckedCount>0)
            return Qt::PartiallyChecked;
    }
    if(unCheckedCount>0)
        return Qt::Unchecked;
    return Qt::Checked;
}

void ComponentPage::treeItem_CheckChildChanged ( QStandardItem * item )
{
    if(nullptr == item)
        return;
    Qt::CheckState siblingState = checkSibling(item);
    QStandardItem * parentItem = item->parent();
    if(nullptr == parentItem)
        return;
    if(Qt::PartiallyChecked == siblingState)
    {
        if(parentItem->isCheckable() && parentItem->isTristate())
            parentItem->setCheckState(Qt::PartiallyChecked);
    }
    else if(Qt::Checked == siblingState)
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Checked);
    }
    else
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Unchecked);
    }
    treeItem_CheckChildChanged(parentItem);
}

void ComponentPage::treeItemChanged ( QStandardItem * item )
{
    if ( item == nullptr )
        return ;
    if ( item->isCheckable())
    {
        // Если у элемента есть флажок, то переходим к следующей операции
        Qt::CheckState state = item->checkState (); // Получить текущий статус выбора
        if ( item->isTristate ())
        {
            // Если запись трехступенчатая, это означает, что вы можете выбрать все и отменить выбор всех подкаталогов
            if ( state != Qt::PartiallyChecked )
            {
                // Выбрано в данный момент, вам нужно выбрать все его подпункты
                treeItem_checkAllChild ( item , state == Qt::Checked ? true : false );
            }
        }
        else
        {
            // Это означает, что есть два состояния, которые повлияют на три состояния родителя
            // Оценка ситуации с родственными узлами
            treeItem_CheckChildChanged ( item );
        }
    }
}

void ComponentPage::treeItem_checkAllChild(QStandardItem * item, bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}

void ComponentPage::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}


ComponentPage::~ComponentPage()
{
    delete ui;
}
