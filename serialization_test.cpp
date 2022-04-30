#include <iostream>
#include <fstream>
#include <string>

#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include "Block.h"
#include "User.h"

using namespace std;

void save_block(const User &s, const char *filename) {
    // make an archive
    ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << s;
}

void restore_block(User &s, const char *filename) {
    ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);
    ia >> s;
}

int main(int argc, char *argv[]) {
    User u1;
    User u2;
    u1.dbg();
    u2.dbg();
    Transaction t(u1.getCPKey(), u2.getCPKey(), ZINA(10), "HW!");
    t.dbg();
    u1.signTransaction(t);
    t.dbg();
    std::cerr << t.getValueHash() << std::endl;
    Block b;
    b.addTransaction(t);

    // display the complete schedule
    cout << "original block";
    b.dbg();

    string filename(boost::archive::tmpdir());
    filename += "/demofile.txt";

    // save the schedule
    save_block(u1, filename.c_str());

    // ... some time later
    // make  a new schedule
    User new_schedule;

    restore_block(new_schedule, filename.c_str());

    // and display
    cout << "\nrestored schedule";
    new_schedule.dbg();
    // should be the same as the old one. (except for the pointer values)
}
