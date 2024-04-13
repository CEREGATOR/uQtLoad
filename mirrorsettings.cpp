#include "mirrorsettings.h"
#include "ui_mirrorsettings.h"

MirrorSettings::MirrorSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MirrorSettings)
{
    ui->setupUi(this);

//    ui->label->setText(tr("Mirror Settings"));

    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&MirrorSettings::s_closeApp);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&MirrorSettings::s_nextPage);
}

MirrorSettings::~MirrorSettings()
{
    delete ui;
}
