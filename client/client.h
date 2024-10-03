#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QWidget>

class Client: public QObject {
    Q_OBJECT

public:
    Client();

public slots:
    void connectToServer();
    void disconnectFromServer();

private slots:
    void onConnected();
    void onReadyRead();

signals:
    void updateClientCount(int count);
    void connectionStatusChanged(bool isConnected);

private:
    QTcpSocket *socket;
    int lastClientCount =- 1;

};


#endif // CLIENT_H
