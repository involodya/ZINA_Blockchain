#include "addtransactiondialog.h"
#include "ui_addtransactiondialog.h"
#include <algorithm>

AddTransactionDialog::AddTransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTransactionDialog)
{
    ui->setupUi(this);
}

AddTransactionDialog::~AddTransactionDialog()
{
    delete ui;
}

void AddTransactionDialog::on_Commit_button_clicked()
{

    std::cerr << "1" << std::endl;
    std::string hash_as_string = (ui->input_hash->displayText()).toStdString();
//    std::cout << s << std::endl;
//    assert(s.length() == 66); // TODO: not assert, but message on screen
    uint8_t* my_hash = new uint8_t[COMPRESSED_PUBLIC_KEY_SIZE];
    // std::unordered_map<char, uint8_t> hex;
    // for (uint8_t i = 0; i < 10; ++i) {
    //     hex['0' + i] = i;
    // }
    // for (uint8_t i = 0; i < 6; ++i) {
    //     hex['a' + i] = i + 10;
    // }
    std::cerr << "2" << std::endl;
    for (int i = 2; i < COMPRESSED_PUBLIC_KEY_SIZE + 2; ++i) {
        my_hash[i - 2] = static_cast<uint8_t>(hash_as_string[i]);
        // my_hash[i/2 - 1] = hex[hash_as_string[i]] * 16 + hex[hash_as_string[i + 1]];
    }
    // dialog_recipient.data_ = reinterpret_cast<uint8_t*>(&hash_as_string[0]);
    std::cerr << "3" << std::endl;
    dialog_recipient.set(my_hash);
    dialog_recipient.dbg();
    std::cerr << "4" << std::endl;
    std::string val = (ui->input_value->displayText()).toStdString();
    if (val == "") val = "0";
    std::string decimal_part = val, fractional_part = "0";
    for (size_t i = 0; i < val.size(); ++i) {
        if (val[i] == '.') {
            decimal_part = val.substr(0, i);
            fractional_part = val.substr(i + 1);
            break;
        }
    }
    dialog_value = {std::stoull(decimal_part), std::stoull(fractional_part)};

    dialog_message = (ui->input_message->displayText()).toStdString();
    close();
    // TODO: confirmation window
//    QDialog show_transaction;
//    Transaction current_transaction(dialog_recipient, dialog_recipient, dialog_value, dialog_message);
//    std::string x = "Your hash: " + hash_as_string + "\nHash of recipient: " + hash_as_string +
//    "\nValue: " + std::to_string(dialog_value._integer_part) + "."
//    + std::to_string(dialog_value._fractional_part)
//    + "\nMessage: " + dialog_message + '\n';
//    QString output = QString::fromStdString(x);
//    show_transaction.addAction(buttonBox);
//    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
//                                     | QDialogButtonBox::Cancel);

    //    show_transaction.setTextValue(output);
//    show_transaction.setWindowTitle("Your transaction");
//    QString name_of_cancel_button =
//    show_transaction.setCancelButtonText(QString::fromStdString("Cancel transaction"));
//    show_transaction.setOkButtonText(QString::fromStdString("Accept transaction"));
//    show_transaction.addButton()
//    show_transaction.exec();

}
/*
0xabobaabobaabobaabobaabobaabobaabobaabobaabobaabobaabobaaboba1234 - correct hash to test
0xabobaabobaabobaabobaabobaabobaabobaabobaabobaabobaabobaaboba123456 - correct CPKey to test
*/
