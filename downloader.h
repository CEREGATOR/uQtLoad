#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

signals:
    void onReady();
    void s_setValueProgress(qint64 bytesRead,qint64 totalBytes);

public slots:
    void getData(const QString& savePath, const QUrl& url);
    void onResult(QNetworkReply *reply);

private:
    QString pathSave;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
};

#endif // DOWNLOADER_H
