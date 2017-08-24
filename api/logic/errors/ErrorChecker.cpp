#include "ErrorChecker.h"
#include "Env.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

ErrorChecker::ErrorChecker(const QString& checkUrl)
{
    m_checkUrl = checkUrl;
}

void ErrorChecker::reloadErrors()
{
    qDebug() << "Reloading errors.";

    NetJob* job = new NetJob("Error JSON Blob");
    auto entry = ENV.metacache()->resolveEntry("root", "errors.json");
    entry->setStale(true);
    job->addNetAction(m_download = Net::Download::makeCached(QUrl(m_checkUrl), entry));
    connect(m_download.get(), &Net::Download::succeeded, this, &ErrorChecker::jsonDownloadFinished);
}

void ErrorChecker::jsonDownloadFinished()
{
    QFile file(m_download->getTargetFilepath());
    if (file.open(QFile::ReadOnly))
    {
        QJsonArray root = QJsonDocument::fromJson(file.readAll()).array();
        for (auto it = root.begin(); it != root.end(); ++it)
        {
            QJsonObject obj = (*it).toObject();
            Error err;
            err.re = QRegExp(obj.value("re").toString());
            // TODO: Parse to QRegExp flags
            err.flags = obj.value("flags").toString();

            // TODO: Get locale
            err.msg = obj.value("msg").toString();

            m_errors.append(err);
        }
    }
}
