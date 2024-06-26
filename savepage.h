#ifndef SAVEPAGE_H
#define SAVEPAGE_H

#include <QWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include "downloader.h"

namespace Ui {
class SavePage;
}

class SavePage : public QWidget
{
    Q_OBJECT

public:
    explicit SavePage(QWidget *parent = nullptr);
    ~SavePage();

public slots:
    void setProgress(qint64 bytesRead,qint64 totalBytes);
    void nextDownload();
    void setUrls(QVector<QUrl> v_urls)
    {
        urls = v_urls;
    }

private slots:
    void startDownload();
    void selectPath();

signals:
    void s_prevPage();

private:
    size_t curDowload;
    QVector<Downloader*> downloaders;
    QVector<QUrl> urls;
    QString pathSave_ = "";
    Ui::SavePage *ui;
};

#endif // SAVEPAGE_H
