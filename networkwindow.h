#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkAccessManager>

namespace Ui {
    class NetworkWindow;
}

class QTcpServer;

class NetworkWindow : public QMainWindow {
Q_OBJECT

public:
    explicit NetworkWindow(size_t port = 33333, QWidget *parent = 0);

    ~NetworkWindow();

private slots:
    void on_starting_clicked();

    void on_requesting_clicked();

    void on_stopping_clicked();

    void newuser();

    void slotReadClient();

    void managerFinished(QNetworkReply *reply);

private:
    Ui::NetworkWindow *ui;
    QTcpServer *tcpServer;
    int server_status;
    QMap<int, QTcpSocket *> SClients;
    size_t port;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

    //TODO delete
    friend int main(int argc, char *argv[]);
};

#endif // MAINWINDOW_H
