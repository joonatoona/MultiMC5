#pragma once
#include <QObject>

#include "net/NetJob.h"
#include "net/Download.h"

#include "multimc_logic_export.h"

class MULTIMC_LOGIC_EXPORT ErrorChecker : public QObject
{
    Q_OBJECT
public:
    ErrorChecker(const QString& checkUrl);

    void Q_SLOT reloadErrors();

    struct Error
    {
        QRegExp re;
        QString flags;
        QString msg;
    };

    QList<Error> getErrors() const;

signals:
    void errorsLoaded();

protected slots:
    void jsonDownloadFinished();

private:
    QString m_checkUrl;
    QList<Error> m_errors;
    bool m_errorLoaded;
    QByteArray errorData;
    QString m_lastLoadError;
    Net::Download::Ptr m_download;

};