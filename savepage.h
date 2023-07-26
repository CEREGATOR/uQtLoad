#ifndef SAVEPAGE_H
#define SAVEPAGE_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class SavePage;
}

class SavePage : public QWidget
{
    Q_OBJECT

public:
    explicit SavePage(QWidget *parent = nullptr);
    ~SavePage();
    QString getPathSave(){return pathSave_;}

private slots:
    void selectPath();

signals:
    void s_prevPage();

private:
    QString pathSave_;
    Ui::SavePage *ui;
};

#endif // SAVEPAGE_H
