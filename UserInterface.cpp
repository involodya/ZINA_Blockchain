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


void UserInterface::on_Commit_hash_clicked()
{
    std::string s = (ui->input_hash->displayText()).toStdString();
//    assert(s.length() == 66); // TODO: not assert, but message on screen
    uint8_t* my_hash = new uint8_t[32];
    std::unordered_map<char, uint8_t> hex;
    for (uint8_t i = 0; i < 10; ++i) {
        hex['0' + i] = i;
    }
    for (uint8_t i = 0; i < 6; ++i) {
        hex['a' + i] = i + 10;
    }
    for (int i = 2; i < 66; i += 2) {
        my_hash[i/2 - 1] = hex[s[i]] * 16 + hex[s[i + 1]];
    }
//    recipient._hash = reinterpret_cast<uint8_t*>(&s[0]);
    recipient._hash = my_hash;
    recipient.dbg();
}
