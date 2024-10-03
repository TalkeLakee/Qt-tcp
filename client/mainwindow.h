#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Client;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Client *client;
    void updateStatusLabel(bool isConnected);
    void updateClientCount(int count);

private slots:
    void on_disconnectButton_clicked();
};

#endif // MAINWINDOW_H
