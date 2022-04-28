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
    std::string hash_as_string = (ui->input_hash->displayText()).toStdString();
    std::cout << hash_as_string << std::endl;
//    assert(s.length() == 66); // TODO: not assert, but message on screen
    uint8_t* my_hash = new uint8_t[COMPRESSED_PUBLIC_KEY_SIZE];
    static std::unordered_map<char, uint8_t> hex = {{'0', 0},
                                                {'1', 1},
                                                {'2', 2},
                                                {'3', 3},
                                                {'4', 4},
                                                {'5', 5},
                                                {'6', 6},
                                                {'7', 7},
                                                {'8', 8},
                                                {'9', 9},
                                                {'a', 10},
                                                {'b', 11},
                                                {'c', 12},
                                                {'d', 13},
                                                {'e', 14},
                                                {'f', 15}};
    for (int i = 2; i < COMPRESSED_PUBLIC_KEY_SIZE * 2 + 2; i += 2) {
        my_hash[i/2 - 1] = hex[hash_as_string[i]] * 16 + hex[hash_as_string[i + 1]];
    }
    dialog_recipient.set(my_hash);
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
    // 0x02f4eccff619b222afee90ff3f6652a85ddc49c4c1be8b46779cdf44ee4b12580c - correct CPKey to test

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
0x21d5599927a5454346b67f6ebd8c687a79bc0155482a6a6d8b93792955c414e312 - correct CPKey to test
0xabobaabobaabobaabobaabobaabobaabobaabobaabobaabobaabobaaboba1234 - correct hash to test
*/

