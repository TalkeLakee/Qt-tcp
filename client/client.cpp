#include "client.h"
#include <QDataStream>

Client::Client() {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
}

void Client::connectToServer() {
    socket->connectToHost(QHostAddress::LocalHost, 8080);
}

void Client::onConnected() {
    qDebug() << "Connected to server";
    emit connectionStatusChanged(true);
}



void Client::onReadyRead() {
    QByteArray data = socket->readAll();

    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_15);

    int clientCount = 0;
    in >> clientCount;

    if (clientCount != lastClientCount) {
        emit updateClientCount(clientCount);
        lastClientCount = clientCount;
    }
}

void Client::disconnectFromServer() {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
        emit connectionStatusChanged(false);
        emit updateClientCount(0);
    }
}

