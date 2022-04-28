#include "UserInterface.h"
#include "addtransactiondialog.h"
#include "./ui_UserInterface.h"
UserInterface::UserInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserInterface)
{
    ui->setupUi(this);
//    local_blockchain = BlockChain();
//    local_blockchain.update();
//    *current_balances = Balances(local_blockchain._verified_chain);
}

UserInterface::~UserInterface()
{
    delete ui;
}


//void UserInterface::on_Commit_hash_clicked()
//{
//    std::string s = (ui->input_hash->displayText()).toStdString();
////    assert(s.length() == 66); // TODO: not assert, but message on screen
//    uint8_t* my_hash = new uint8_t[32];
//    std::unordered_map<char, uint8_t> hex;
//    for (uint8_t i = 0; i < 10; ++i) {
//        hex['0' + i] = i;
//    }
//    for (uint8_t i = 0; i < 6; ++i) {
//        hex['a' + i] = i + 10;
//    }
//    for (int i = 2; i < 66; i += 2) {
//        my_hash[i/2 - 1] = hex[s[i]] * 16 + hex[s[i + 1]];
//    }
////    recipient._hash = reinterpret_cast<uint8_t*>(&s[0]);
//    recipient._hash = my_hash;
//    recipient.dbg();
//}

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
    Transaction new_transaction(this_user.getCPKey(), dial.dialog_recipient, dial.dialog_value, dial.dialog_message);
    this_user.signTransaction(new_transaction);
    new_transaction.dbg();
    this_user.sendTransaction(new_transaction);
}
