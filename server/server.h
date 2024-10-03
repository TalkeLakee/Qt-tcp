#ifndef SERVER_H
#define SERVER_H

#include<QTcpServer>
#include<QTcpSocket>
#include<QObject>
#include<QString>
#include<QVector>


class Server : public QTcpServer {
    Q_OBJECT

public:
    Server();
    ~Server();

private slots:
    void onClientDisconnected();
    void incomingConnection(qintptr socketDescriptor);
    void broadcastClientCount();

private:
    QVector<QTcpSocket*> clients;
};

#endif // SERVER_H
