#include "UserInterface.h"
#include "./ui_UserInterface.h"
#include "Hash.h"

UserInterface::UserInterface(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::UserInterface) {
    ui->setupUi(this);
}

UserInterface::~UserInterface() {
    delete ui;
}


void UserInterface::on_Commit_hash_clicked() {
    std::string s = (ui->input_hash->displayText()).toStdString();
//    assert(s.length() == 66); // TODO: not assert, but message on screen
    recipient.set(s);
    recipient.dbg();
}
