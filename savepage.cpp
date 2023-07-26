#include "savepage.h"
#include "ui_savepage.h"
#include "downloader.h"


SavePage::SavePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavePage)
{
    ui->setupUi(this);

    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&SavePage::s_prevPage);

    connect(ui->openButton,&QPushButton::clicked,this,&SavePage::selectPath);
}

void SavePage::selectPath()
{
    QString pathSave_ = QFileDialog::getExistingDirectory(
                this,
                "Путь сохранения",
                "../");

    ui->pathSaveLine->setText(pathSave_);


    Downloader* downloader = new Downloader();
    downloader->setPath(pathSave_);
    downloader->getData();

//    ui->pathSaveLine->setText(QDir::tempPath());
}

SavePage::~SavePage()
{
    delete ui;
}
