#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>

namespace Ui {
    class NetworkWindow;
}

class QTcpServer;

class NetworkWindow : public QMainWindow {
Q_OBJECT

public:
    explicit NetworkWindow(QWidget *parent = 0);

    ~NetworkWindow();

private slots:

    void on_starting_clicked();

    void on_stoping_clicked();

    void newuser();

    void slotReadClient();

private:
    Ui::NetworkWindow *ui;
    QTcpServer *tcpServer;
    int server_status;
    QMap<int, QTcpSocket *> SClients;
};

#endif // MAINWINDOW_H
