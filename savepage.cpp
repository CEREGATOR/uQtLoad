#include "savepage.h"
#include "ui_savepage.h"
#include <q7z_extract.h>
#include <q7z_facade.h>

SavePage::SavePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavePage)
{
    ui->setupUi(this);

//    ui->label->setText(tr("Save Qt"));

    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&SavePage::s_prevPage);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&SavePage::startDownload);

    connect(ui->openButton,&QPushButton::clicked,this,&SavePage::selectPath);

    ui->progressBar->show();

    Q7z::initSevenZ();
}

void SavePage::selectPath()
{
    QString path = QFileDialog::getExistingDirectory(
                this,
                tr("Select folder"),
                QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    pathSave_ = path+"/"+"Qt";
//    pathSave_+=QString("/"+"Qt");

    ui->pathSaveLine->setText(pathSave_);
}

void SavePage::startDownload()
{
    ui->textBrowser->append(tr("Start dowload"));

//    urls.push_back(QUrl("https://w.forfun.com/fetch/db/db6e862725f8e449427d1de5b2be0835.jpeg"));
//    urls.push_back(QUrl("https://mirror.accum.se/mirror/qt.io/qtproject/online/qtsdkrepository/windows_x86/desktop/qt5_5152/qt.qt5.5152.win32_msvc2019/5.15.2-0-202011130602qtbase-Windows-Windows_10-MSVC2019-Windows-Windows_10-X86.7z"));
//    urls.push_back(QUrl("https://mirror.accum.se/mirror/qt.io/qtproject/online/qtsdkrepository/windows_x86/desktop/qt5_5152/qt.qt5.5152.win32_msvc2019/5.15.2-0-202011130602qttools-Windows-Windows_10-MSVC2019-Windows-Windows_10-X86.7z"));
//    urls.push_back(QUrl("https://mirror.accum.se/mirror/qt.io/qtproject/official_releases/qtcreator/10.0/10.0.1/installer_source/windows_x64/qtcreator.7z"));
//    urls.push_back(QUrl("https://mirror.accum.se/mirror/qt.io/qtproject/official_releases/qtcreator/10.0/10.0.1/installer_source/windows_x64/qtcreatorcdbext.7z"));

    for(size_t i=0;i<urls.size();i++)
    {
        downloaders.push_back(new Downloader());
        connect(downloaders.at(i),&Downloader::s_setValueProgress,this,&SavePage::setProgress);
        connect(downloaders.at(i),&Downloader::onReady,this,&SavePage::nextDownload);
    }
    curDowload = 0;

    downloaders.at(curDowload)->getData(QDir::tempPath(),urls.at(curDowload));
}

void SavePage::nextDownload()
{
//    QString zippath = ui->pathSaveLine->text()+"/"+urls.at(curDowload).fileName();
    QString zippath = QDir::tempPath()+"/"+urls.at(curDowload).fileName();

//    QString temp = QDir::tempPath();

    ui->textBrowser->append(tr("Download successfully : %1").arg(zippath));

    QFile source(zippath); // embedded resource
    source.open(QIODevice::ReadOnly);
    Q7z::extractArchive(&source, pathSave_);

    ui->textBrowser->append(tr("Extract successfully : %1").arg(QFileInfo(zippath).completeBaseName()));

    if(curDowload < downloaders.size()-1)
    {
        downloaders.at(++curDowload)->getData(QDir::tempPath(),urls.at(curDowload));
    }
    else
    {
        ui->textBrowser->append(tr("Finish!"));
    }
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
