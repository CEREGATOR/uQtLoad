#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "downloader.h"

#define CURR_PAGE ui->stackedWidget->currentIndex()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("uQtLoad"));

    connect(ui->componentWidget,&ComponentPage::s_nextPage,this,[=](){ui->stackedWidget->setCurrentIndex(CURR_PAGE+1);});
    connect(ui->componentWidget,&ComponentPage::s_prevPage,this,[=](){ui->stackedWidget->setCurrentIndex(CURR_PAGE-1);});

    connect(ui->saveWidget,&SavePage::s_prevPage,this,[=](){ui->stackedWidget->setCurrentIndex(CURR_PAGE-1);});

    connect(ui->mirrorWidget,&MirrorSettings::s_closeApp,this,[=](){this->close();});
    connect(ui->mirrorWidget,&MirrorSettings::s_nextPage,this,[=](){ui->stackedWidget->setCurrentIndex(CURR_PAGE+1);});
}


MainWindow::~MainWindow()
{
    delete ui;
}

