#ifndef MIRRORSETTINGS_H
#define MIRRORSETTINGS_H

#include <QWidget>

namespace Ui {
class MirrorSettings;
}

class MirrorSettings : public QWidget
{
    Q_OBJECT

public:
    explicit MirrorSettings(QWidget *parent = nullptr);
    ~MirrorSettings();

    QStringList getListMirror();

private slots:
    void nextPage();

signals:
    void s_setMirror(QStringList list_mirror);
    void s_closeApp();
    void s_nextPage();

private:
    Ui::MirrorSettings *ui;
    QStringList list_mirror;
};

#endif // MIRRORSETTINGS_H
