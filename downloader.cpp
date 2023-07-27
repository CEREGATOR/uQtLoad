#include "downloader.h"
#include <QDebug>

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    // Initialize manager ...
    manager = new QNetworkAccessManager();
    // ... and connect the signal to the handler

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("proxy.olvs.miee.ru");
    proxy.setPort(8080);

    manager->setProxy(proxy);
    manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData(const QString& savePath, const QUrl& url)
{
    pathSave = savePath+QDir::separator()+url.fileName();
//    qDebug() << savePath;
//    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();

    QNetworkRequest request;
    request.setUrl(url);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    reply = manager->get(request);
    reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();

    connect(reply,&QNetworkReply::downloadProgress,this,&Downloader::s_setValueProgress);
}

void Downloader::onResult(QNetworkReply *reply)
{
    // If an error occurs in the process of obtaining data
    if(reply->error()){
        // We inform about it and show the error information
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        // Otherwise we create an object file for use with
        QFile *file = new QFile(pathSave);
        // Create a file, or open it to overwrite ...
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());  // ... and write all the information from the page file
            file->close();                  // close file
            qDebug() << "Downloading is completed";
            delete file;
            reply->deleteLater();
            emit onReady(); // Sends a signal to the completion of the receipt of the file
        }
    }
}

