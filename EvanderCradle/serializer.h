#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class Serializer
{
public:
    Serializer(const QString &filename);
    bool write(const QString &content, const QString &agent);
    QJsonArray read();

private:
    QString m_filename;
};

#endif // SERIALIZER_H
