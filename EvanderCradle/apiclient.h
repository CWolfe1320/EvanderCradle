#ifndef APICLIENT_H
#define APICLIENT_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>
#include "serializer.h"


class APIClient : public QObject
{
    Q_OBJECT

public:
    APIClient(QString authToken, QString model, QString endpoint, Serializer *serializer);
    void sendRequest(QJsonArray messageContent);
    QString getLastResponse();

signals:
    void responseReceived(QString message);

private:
    QNetworkAccessManager *manager;
    QString authToken;
    QString model;
    QString endpoint;
    Serializer* serializer;

private slots:
    void onResponse(QNetworkReply *reply);
};

#endif // APICLIENT_H
