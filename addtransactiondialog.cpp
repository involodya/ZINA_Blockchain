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
    std::string hash_as_string = (ui->input_hash->displayText()).toStdString();
    bool correctly_proceed = true;
    if (hash_as_string.length() != COMPRESSED_PUBLIC_KEY_SIZE * 2 + 2) {
        QMessageBox warning;
        warning.setStyleSheet(QString::fromStdString(color_of_interface));
        QString output = QString::fromStdString("Check hash of receiver: it has inappropriate size");
        warning.setText(output);
        warning.setWindowTitle("Warning");
        correctly_proceed = false;
        warning.exec();
        close();
    }
    if (!correctly_proceed) close();
    if (hash_as_string.substr(0, 4) != "0x02" && correctly_proceed) {
        QMessageBox warning;
        warning.setStyleSheet(QString::fromStdString(color_of_interface));
        QString output = QString::fromStdString("Check hash of receiver: it must have prefix \'0x02\'");
        warning.setText(output);
        warning.setWindowTitle("Warning");
        correctly_proceed = false;
        warning.exec();
        close();
    }
    if (!correctly_proceed) close();
    uint8_t* my_hash = new uint8_t[COMPRESSED_PUBLIC_KEY_SIZE];

    for (size_t i = 2; i < COMPRESSED_PUBLIC_KEY_SIZE * 2 + 2; i += 2) {
        my_hash[i/2 - 1] = hex[hash_as_string[i]] * 16 + hex[hash_as_string[i + 1]];
    }
    dialog_recipient.set(my_hash);
    dialog_recipient.dbg();
    // Proceed hash, proceeding value now

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
    if (fractional_part.length() > ZINA::NUMBER_OF_DECIMAL_PLACES && correctly_proceed) {
        QMessageBox warning;
        warning.setStyleSheet(QString::fromStdString(color_of_interface));
        QString output = QString::fromStdString("Incorrect value: fractional part size must be <= "
                                                + std::to_string(ZINA::NUMBER_OF_DECIMAL_PLACES));
        warning.setText(output);
        warning.setWindowTitle("Warning");
        correctly_proceed = false;
        warning.exec();
        close();
    }
    if (!correctly_proceed) close();
    fractional_part += std::string(ZINA::NUMBER_OF_DECIMAL_PLACES - fractional_part.size(), '0');
    try {
        dialog_value = {std::stoull(decimal_part), std::stoull(fractional_part)};
    }  catch (...) {
        QMessageBox warning;
        warning.setStyleSheet(QString::fromStdString(color_of_interface));
        QString output = QString::fromStdString("Incorrect value");
        warning.setText(output);
        warning.setWindowTitle("Warning");
        correctly_proceed = false;
        warning.exec();
        close();
    }
    if (!correctly_proceed) close();
    // Processed

    dialog_message = (ui->input_message->displayText()).toStdString();
//    std::cerr << "1" << std::endl;

    if (correctly_proceed) {
        ConfirmationWindow confirm;
        confirm.exec();
        accepted_to_be_sent = confirm.answer;
    }

    close();
    // 0x02f4eccff619b222afee90ff3f6652a85ddc49c4c1be8b46779cdf44ee4b12580c - correct CPKey to test

}
/*

0x01d5599927a5454346b67f6ebd8c687a79bc0155482a6a6d8b93792955c414e312 - correct CPKey to test
0xabobaabobaabobaabobaabobaabobaabobaabobaabobaabobaabobaaboba1234 - correct hash to test
*/


void AddTransactionDialog::on_CancelButton_clicked()
{
    close();
}
