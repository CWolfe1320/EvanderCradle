#include "mainwindow.h"
#include "apiclient.h"
#include "serializer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Serializer mixtral("mixtral.txt");

    APIClient apiClient("{authToken}", "mixtral-8x7b-32768", "https://api.groq.com/openai/v1/chat/completions", &mixtral);

    mixtral.write("Ooh! Aiden is a great name. As a test could you tell me what I just asked you to call me?", "user");

    apiClient.sendRequest(mixtral.read());

    return a.exec();
}
