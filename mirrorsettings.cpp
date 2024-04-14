#include "mirrorsettings.h"
#include "ui_mirrorsettings.h"

MirrorSettings::MirrorSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MirrorSettings)
{
    ui->setupUi(this);

    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&MirrorSettings::s_closeApp);
//    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&MirrorSettings::s_nextPage);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&MirrorSettings::nextPage);

    //    ui->mirror_textEdit->setText(mirror_textEdit->text() + "https://mirror.accum.se/mirror/qt.io/qtproject/");
    list_mirror << "https://mirror.accum.se/mirror/qt.io/qtproject/"<<"\n"<<"https://mirror.accum.se/mirror/qt.io/";
    for(auto l : list_mirror)
        ui->mirror_textEdit->insertPlainText(l);
    //    ui->mirror_textEdit->insertPlainText();
}

QStringList MirrorSettings::getListMirror()
{
    return list_mirror;
}

void MirrorSettings::nextPage()
{
    emit s_setMirror(list_mirror);
    emit s_nextPage();
}

MirrorSettings::~MirrorSettings()
{
    delete ui;
}
