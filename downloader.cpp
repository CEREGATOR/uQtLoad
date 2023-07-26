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

//    manager->setProxy(proxy);
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData()
{
    QString zip = "https://mirror.accum.se/mirror/qt.io/qtproject/online/qtsdkrepository/windows_x86/desktop/qt5_5152/qt.qt5.5152.win32_msvc2019/5.15.2-0-202011130602qtbase-Windows-Windows_10-MSVC2019-Windows-Windows_10-X86.7z";
    QUrl url(zip);
    QFileInfo fileInfo(url.path());
    savePath+="/"+fileInfo.fileName();
    qDebug() << savePath;
    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();

    QNetworkRequest request;
    request.setUrl(url);
    reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
    reply = manager->get(request);

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
        QFile *file = new QFile(savePath);
        // Create a file, or open it to overwrite ...
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());  // ... and write all the information from the page file
            file->close();                  // close file
        qDebug() << "Downloading is completed";
        emit onReady(); // Sends a signal to the completion of the receipt of the file
        }
    }
}

void Downloader::updateDownloadProgress(qint64 bytesRead, qint64 totalBytes)
{
}
