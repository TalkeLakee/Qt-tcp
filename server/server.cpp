#include "server.h"


Server::Server() {
    if (this->listen(QHostAddress::LocalHost, 8080)) {
        qDebug() << "Server started successfully";
    } else {
        qDebug() << "Error on server start";
    }
}

Server::~Server() {
    for (QTcpSocket* client : clients) {
        client->close();
        client->deleteLater();
    }
    this->close();
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    clients.push_back(socket);

    connect(socket, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);

    qDebug() << "Current number: " << clients.size() << " " << "Client connected from IP: " << socket->peerAddress().toString();

    broadcastClientCount();
}

void Server::onClientDisconnected() {
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    clients.removeOne(client);
    client->deleteLater();

    qDebug() << "Client disconnected. Current number of clients: " << clients.size();

    broadcastClientCount();
}

void Server::broadcastClientCount() {
    int clientCount = clients.size();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << clientCount;

    qDebug() << "Broadcst client count: " << clients.size();

    for (QTcpSocket *client: clients) {
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(block);
            qDebug() << "Sent client count:" << clientCount << "to client:" << client->peerAddress().toString();
        }
    }

}

