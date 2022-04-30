#include "networkwindow.h"
#include "ui_networkwindow.h"

NetworkWindow::NetworkWindow(size_t port, QWidget *parent) :
        port(port), QMainWindow(parent), ui(new Ui::NetworkWindow), manager(new QNetworkAccessManager()) {
    ui->setupUi(this);
    ui->textinfo->append(QString::fromUtf8("port: ") + QString::number(port) + "\n\r");

    QObject::connect(manager, SIGNAL(finished(QNetworkReply * )),
                     this, SLOT(managerFinished(QNetworkReply * )));
}

NetworkWindow::~NetworkWindow() {
    delete ui;
    delete manager;
    server_status = 0;
}

void NetworkWindow::on_starting_clicked() {
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!tcpServer->listen(QHostAddress::Any, port) && server_status == 0) {
        qDebug() << QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
        ui->textinfo->append(tcpServer->errorString());
    } else {
        server_status = 1;
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
        ui->textinfo->append(QString::fromUtf8("Сервер запущен!"));
        qDebug() << QString::fromUtf8("Сервер запущен!");
    }
}

void NetworkWindow::on_stopping_clicked() {
    if (server_status == 1) {
                foreach(int i, SClients.keys()) {
                QTextStream os(SClients[i]);
                os.setAutoDetectUnicode(true);
                os << QDateTime::currentDateTime().toString() << "\n";
                SClients[i]->close();
                SClients.remove(i);
            }
        tcpServer->close();
        ui->textinfo->append(QString::fromUtf8("Сервер остановлен!"));
        qDebug() << QString::fromUtf8("Сервер остановлен!");
        server_status = 0;
    }
}


void NetworkWindow::newuser() {
    if (server_status == 1) {
        qDebug() << QString::fromUtf8("У нас новое соединение!");
        ui->textinfo->append(QString::fromUtf8("У нас новое соединение!"));
        QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
        int idusersocs = clientSocket->socketDescriptor();
        SClients[idusersocs] = clientSocket;
        connect(SClients[idusersocs], SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    }
}

void NetworkWindow::slotReadClient() {
    QTcpSocket *clientSocket = (QTcpSocket *) sender();
    int idusersocs = clientSocket->socketDescriptor();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
    os << "HTTP/1.0 200 Ok\r\n"
          "Content-Type: text/html; charset=\"utf-8\"\r\n"
          "\r\n"
          "<h1>Nothing to see here</h1>\n"
       << QDateTime::currentDateTime().toString() << "\n";
    ui->textinfo->append("ReadClient:" + clientSocket->readAll() + "\n\r");
    // Если нужно закрыть сокет
    clientSocket->close();
    SClients.remove(idusersocs);
}

void NetworkWindow::on_requesting_clicked() {
    request.setUrl(QUrl("http://localhost:33333"));
    manager->get(request);
}

void NetworkWindow::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();
    ui->textinfo->append(answer + "\n\r");
    qDebug() << answer;
}
