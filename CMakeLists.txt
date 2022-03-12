cmake_minimum_required(VERSION 3.21)
project(ZINA_Blockchain)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ZINA_Blockchain
        AllTransactions.h
        Block.h
        BlockChain.h
        definitions.h
        hash_functions.h
        main.cpp
        Miner.h
        test.cpp
        Transaction.h
        User.cpp
        User.h)
