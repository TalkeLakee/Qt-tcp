#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    client = new Client();

    connect(client, &Client::updateClientCount, this, &MainWindow::updateClientCount);
    connect(client, &Client::connectionStatusChanged, this, &MainWindow::updateStatusLabel);
    connect(ui->pushButton_connect, &QPushButton::clicked, client, &Client::connectToServer);
}

void MainWindow::updateClientCount(int count) {
    if (count == 0) {
        ui->label_clientCount->setText("");
    } else {
        ui->label_clientCount->setText(QString("Connected Clients: %1").arg(count));
    }
}

void MainWindow::on_disconnectButton_clicked() {
    if (client) {
        client->disconnectFromServer();
        qDebug() << "Disconnected from server.";
    }
}

void MainWindow::updateStatusLabel(bool isConnected) {
    if (isConnected) {
        ui->statusLabel->setText("Online");
        ui->statusLabel->setStyleSheet("color: green;");
    } else {
        ui->statusLabel->setText("Offline");
        ui->statusLabel->setStyleSheet("color: red;");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
