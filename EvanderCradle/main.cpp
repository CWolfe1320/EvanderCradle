#include "mainwindow.h"
#include "apiclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    APIClient apiClient("authToken here", "mixtral-8x7b-32768", "https://api.groq.com/openai/v1/chat/completions");

    QString messageContent = "Hey mixtral! How are you today?";

    apiClient.sendRequest(messageContent);

    return a.exec();
}
