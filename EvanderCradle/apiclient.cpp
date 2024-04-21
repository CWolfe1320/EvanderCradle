#include "apiclient.h"

APIClient::APIClient(QString authToken, QString model, QString endpoint, Serializer *serializer) : authToken(authToken), model(model), endpoint(endpoint), serializer(serializer){
    this->manager = new QNetworkAccessManager(this);
    QObject::connect(this->manager, &QNetworkAccessManager::finished, this, &APIClient::onResponse);
}

void APIClient::sendRequest(QJsonArray messagesArray){
    QUrl url(this->endpoint);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + this->authToken.toUtf8());

    QJsonObject rootObject;
    rootObject["messages"] = messagesArray;
    rootObject["model"] = this->model;

    QJsonDocument doc(rootObject);
    QByteArray data = doc.toJson();

    this->manager->post(request, data);
}

void APIClient::onResponse(QNetworkReply *reply){
    if(reply->error()){
        QTextStream(stdout) << "Reply from server, error: " << reply->errorString() << Qt::endl;
    }
    else{

        QByteArray responseData = reply->readAll();

        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &jsonError);

        if(jsonError.error == QJsonParseError::NoError){
            if(jsonDoc.isObject() && !jsonDoc.isEmpty()){
                QJsonObject rootObj = jsonDoc.object();

                if(rootObj.contains("choices") && rootObj["choices"].isArray()){
                    QJsonArray choicesArray = rootObj["choices"].toArray();

                    if(choicesArray.first().isObject() && !choicesArray.isEmpty()){
                        QJsonObject firstChoiceObj = choicesArray.first().toObject();

                        if(firstChoiceObj.contains("message") && firstChoiceObj["message"].isObject()){
                            QJsonObject messageObj = firstChoiceObj["message"].toObject();

                            if(messageObj.contains("content") && messageObj["content"].isString()){
                                QString content = messageObj["content"].toString();

                                QTextStream(stdout) << content << Qt::endl;

                                this->serializer->write(content,"assistant");
                            }
                        }
                    }
                }
            }
        }
        else{
            QTextStream(stdout) << "JSON parsing error: " << jsonError.errorString() << Qt::endl;
        }
    }
    reply->deleteLater();
}
