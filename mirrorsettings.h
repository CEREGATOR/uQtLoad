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

signals:
    void s_closeApp();
    void s_nextPage();

private:
    Ui::MirrorSettings *ui;
};

#endif // MIRRORSETTINGS_H
