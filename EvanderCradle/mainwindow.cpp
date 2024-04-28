#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(APIClient *apiclient, QWidget *parent)
    : apiClient(apiclient), QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->apiClient, &APIClient::responseReceived, this, &MainWindow::onResponseReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString sendText = ui->input->toPlainText();

    if(!sendText.isEmpty()){
        ui->chatWindow->append("<b><font color=\"#A75F75\">Corey</font color></b>: <p>" + sendText + "</p>");

        this->serializer->write(sendText, "user");

        apiClient->sendRequest(this->serializer->read());

        ui->input->clear();
    }
}

void MainWindow::setSerializer(Serializer *serializer) {
    this->serializer = serializer;
}

void MainWindow::setAPIClient(APIClient *apiClient){
    this->apiClient = apiClient;
}

void MainWindow::onResponseReceived(QString message){
    message.replace("\n","<br/>");
    ui->chatWindow->append("<b><font color=\"#87CEEB\">Evander</font color></b>: <p>" + message + "</p>");
}
