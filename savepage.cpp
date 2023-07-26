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

    ui->progressBar->show();
}

void SavePage::selectPath()
{
    QString pathSave_ = QFileDialog::getExistingDirectory(
                this,
                "Путь сохранения",
                "../");

    ui->pathSaveLine->setText(pathSave_);

    Downloader* downloader = new Downloader();

//    connect(downloader,&Downloader::s_setMaxProgress,ui->progressBar,&QProgressBar::setMaximum);
//    connect(downloader,&Downloader::s_setCurrByte,ui->progressBar,&QProgressBar::setValue);

    downloader->setPath(pathSave_);

    connect(downloader,&Downloader::s_setValueProgress,this,&SavePage::setProgress);

    downloader->getData();

//    ui->pathSaveLine->setText(QDir::tempPath());
}

void SavePage::setProgress(qint64 bytesRead,qint64 totalBytes)
{
    ui->progressBar->setValue(bytesRead);
    ui->progressBar->setMaximum(totalBytes);
}

SavePage::~SavePage()
{
    delete ui;
}
