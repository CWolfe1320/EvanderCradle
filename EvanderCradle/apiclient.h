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


class APIClient : public QObject
{
    Q_OBJECT

public:
    APIClient(QString authToken, QString model, QString endpoint);
    void sendRequest(QString messageContent);


private:
    QNetworkAccessManager *manager;
    QString authToken;
    QString model;
    QString endpoint;

private slots:
    void onResponse(QNetworkReply *reply);
};

#endif // APICLIENT_H
