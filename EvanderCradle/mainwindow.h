#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "apiclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(APIClient *apiclient, QWidget *parent = nullptr);
    void setAPIClient(APIClient *apiclient);
    void setSerializer(Serializer *serializer);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    APIClient *apiClient;
    Serializer *serializer;

private slots:
    void on_sendButton_clicked();
    void onResponseReceived(QString message);
};
#endif // MAINWINDOW_H
