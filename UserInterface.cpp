#include "UserInterface.h"
#include "./ui_UserInterface.h"
UserInterface::UserInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserInterface)
{
    ui->setupUi(this);
}

UserInterface::~UserInterface()
{
    delete ui;
}



void UserInterface::on_Receive_button_clicked()
{
    QMessageBox show_hash;
    std::stringstream s;
    s << this_user.getCPKey();
    std::string x;
    std::getline(s, x);
    QString output = QString::fromStdString(x);
    show_hash.setText(output);
    show_hash.setWindowTitle("Your hash to receice transaction");

    show_hash.exec();
}

void UserInterface::on_Send_button_clicked()
{
    AddTransactionDialog dial;
    dial.exec();
    // std::cerr << "2" << std::endl;
    // std::cerr << this_user.getCPKey() << std::endl;
    if (dial.need_to_send) {
        Transaction new_transaction(this_user.getCPKey(), dial.dialog_recipient, dial.dialog_value, dial.dialog_message);
        // std::cerr << "3" << std::endl;
        this_user.signTransaction(new_transaction);
        new_transaction.dbg();
        this_user.sendTransaction(new_transaction);
    }
}
