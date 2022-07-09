#include "UserInterface.h"
#include "./ui_UserInterface.h"
UserInterface::UserInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserInterface)
    , local_blockchain()
    , current_balances(local_blockchain.get_verified_chain())
{
    ui->setupUi(this);
//    current_balance = current_balances[this_user.getCPKey()];
    current_balance = ZINA(1000);
    // We didn't implement archivation of blockchain yet (and rearchivation too),
    // so let it just be ZINA(1000) as basic balance to make demonstration easier.
    ui->balance_value->setText(QString::fromStdString(current_balance.toString()));
}

UserInterface::~UserInterface()
{
    delete ui;
}



void UserInterface::on_Receive_button_clicked()
{
    QMessageBox show_hash;
    show_hash.setStyleSheet(QString::fromStdString(color_of_interface));
    std::stringstream s;
    s << this_user.getCPKey();
    std::string x;
    std::getline(s, x);
    QString output = QString::fromStdString(x);
    show_hash.setText(output);
    show_hash.setWindowTitle("Your hash to receive transaction");

    show_hash.exec();
}

void UserInterface::on_Send_button_clicked()
{
    AddTransactionDialog dial;
    dial.exec();
    // std::cerr << "2" << std::endl;
    // std::cerr << this_user.getCPKey() << std::endl;
    if (current_balance < dial.dialog_value) {
        QMessageBox warning;
        warning.setStyleSheet(QString::fromStdString(color_of_interface));
        QString output = QString::fromStdString("Your balance ("
                                              + current_balance.toString()
                                              + ") is lower than transaction value ("
                                              + dial.dialog_value.toString() + ").");
        warning.setText(output);
        warning.setWindowTitle("Warning");
        warning.exec();
//        close();
    } else if (dial.accepted_to_be_sent) {
        Transaction new_transaction(this_user.getCPKey(), dial.dialog_recipient, dial.dialog_value, dial.dialog_message);
        // std::cerr << "3" << std::endl;
        current_balance -= dial.dialog_value;
        ui->balance_value->setText(QString::fromStdString(current_balance.toString()));
        this_user.signTransaction(new_transaction);
        new_transaction.dbg();
        this_user.sendTransaction(new_transaction);
    }
}

//        std::cerr << (ui->balance_value->text().toStdString()) << ' ' << current_balance.toString()
//                  << " -those 2 are text() and current_balance respectively" << std::endl;

