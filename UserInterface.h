#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include <BlockChain.h>
#include <Balances.h>
#include <User.h>
#include <QMessageBox>
#include <QWindow>
#include "addtransactiondialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserInterface; }
QT_END_NAMESPACE

class UserInterface : public QMainWindow
{
    Q_OBJECT

public:
    UserInterface(QWidget *parent = nullptr);
    ~UserInterface();
    BlockChain local_blockchain;
    User this_user;
    ZINA current_balance = ZINA(1000);
    Balances current_balances;

//private slots:
//    void on_Commit_hash_clicked();

private slots:
    void on_Receive_button_clicked();

    void on_Send_button_clicked();

private:
    Ui::UserInterface *ui;
};
#endif // USERINTERFACE_H

