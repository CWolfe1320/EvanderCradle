#include "serializer.h"

Serializer::Serializer(const QString &filename) : m_filename(filename) {}

bool Serializer::write(const QString &content, const QString &agent) {
    QJsonArray messageArray = read();

    QJsonObject messageObject;
    messageObject["role"] = agent;
    messageObject["content"] = content;
    messageArray.append(messageObject);

    QJsonDocument doc(messageArray);
    QString jsonString = doc.toJson();

    QFile file(m_filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for writing: " << file.errorString();
        return false;
    }

    QTextStream out(&file);
    out << jsonString;
    file.close();
    return true;
}

QJsonArray Serializer::read() {
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading: " << file.errorString();
        return QJsonArray();
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    if (doc.isArray()) {
        return doc.array();
    } else {
        return QJsonArray();
    }
}
