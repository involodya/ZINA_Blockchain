#include "BlockChain.h"
#include "User.h"

void help() {
    std::cout << "Type \"quit\" or escape to quit\n";
    std::cout << "Type \"Add transaction\" to add transaction\n";
}
/*  */
bool is_similar_to(std::set<std::string> words, std::string word) {
    return words.find(word) != words.end();
}

void client_interface(User& this_user, BlockChain& local_blockchain) {
    std::set<std::string> commands_to_add_transaction;
    commands_to_add_transaction.insert("Add transaction");
    commands_to_add_transaction.insert("add transaction");
    commands_to_add_transaction.insert("Add trans");
    commands_to_add_transaction.insert("add trans");
    commands_to_add_transaction.insert("Add");
    commands_to_add_transaction.insert("add");
    commands_to_add_transaction.insert("New transaction");
    commands_to_add_transaction.insert("new transaction");
    commands_to_add_transaction.insert("New");
    commands_to_add_transaction.insert("new");

    std::set<std::string> commands_to_quit;
    commands_to_quit.insert("Quit");
    commands_to_quit.insert("quit");
    commands_to_quit.insert("Escape");
    commands_to_quit.insert("escape");
    commands_to_quit.insert("Esc");
    commands_to_quit.insert("esc");
    commands_to_quit.insert("Exit");
    commands_to_quit.insert("exit");


    bool running = true;
    help();
    while(running) {
        std::string command;
        std::getline(std::cin, command);
        if (is_similar_to(commands_to_quit, command)) {
            running = false;
            continue;
        }
        else if (is_similar_to(commands_to_add_transaction, command)) {
            std::string hash_of_recipient;
            std::cout << "Enter hash of recipient\n";
            std::cin >> hash_of_recipient;
            
            ZINA value_of_new_transaction;
            try {
                std::cout << "Enter value of transaction as integer and decimal parts of ZINA: e.g. 1 234 = 1.234 ZINAs\n";
                std::cin >> value_of_new_transaction;
            } catch(const std::exception& e) {
                std::cerr << "Exception in entering value_of_new_transaction" << e.what() << '\n';
            }
            Transaction new_transaction(this_user.getHash(), Hash(hash_of_recipient), value_of_new_transaction);
            std::cout << "Are you sure you want to sign this transaction? Yes/No\n";
            std::string confirmation;
            std::cin >> confirmation;
            if (confirmation == "No") {
                std::cout << "Deleted this transaction. You can enter new one\n";
                continue;
            }
            try {
                this_user.signTransaction(new_transaction);
                std::cout << "Succesfully signed transaction\n";
            } catch(const std::exception& e) {
                std::cerr << "Exception in signing transaction" << e.what() << '\n';
            }
            std::cout << "Are you sure you want to send this transaction of " << value_of_new_transaction  
            << " ZINAs to " << hash_of_recipient << " ZINAs? Yes/No\n";
            std::cin >> confirmation;
            if (confirmation == "No") {
                std::cout << "Deleted this transaction. You can enter new one\n";
                continue;
            }
            try {
                this_user.sendTransaction(new_transaction);
                std::cout << "Succesfully sent transaction\n";
            } catch(const std::exception& e) {
                std::cerr << "Exception in sending transaction" << e.what() << '\n';
            }
            continue;
        }
        else if (command == "help") {
            help();
        }
        // TODO:
        // else if (command == "update") {
        //     local_blockchain.update();
        // }
    }
}



int main() {
    User this_user;
    BlockChain local_blockchain;
    // TODO: Connect to local server via libboost
    client_interface(this_user, local_blockchain/*host*/);
    
}