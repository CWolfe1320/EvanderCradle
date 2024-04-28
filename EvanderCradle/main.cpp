#include "mainwindow.h"
#include "apiclient.h"
#include "serializer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Serializer llama3_70("llama3_70.txt");

    APIClient apiClient("{authToken}", "llama3-70b-8192", "https://api.groq.com/openai/v1/chat/completions", &llama3_70);

    MainWindow w(&apiClient, nullptr);

    w.setAPIClient(&apiClient);
    w.setSerializer(&llama3_70);

    w.show();

    return a.exec();
}
