cmake_minimum_required(VERSION 3.18)
project(ZINA_Blockchain)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(ZINA SHARED ZINA.cpp)

add_library(constants SHARED constants.cpp)
target_link_libraries(constants PUBLIC ZINA)

add_library(Transaction SHARED Transaction.cpp)
target_link_libraries(Transaction PUBLIC constants)

add_library(Coinbase SHARED Coinbase.cpp)
target_link_libraries(Coinbase PUBLIC constants)

add_library(Block SHARED Block.cpp)
target_link_libraries(Block PUBLIC constants Transaction)

add_library(hash_functions SHARED hash_functions.cpp)
target_link_libraries(hash_functions PUBLIC Block ssl crypto secp256k1 constants)

add_library(VerifiedChain SHARED VerifiedChain.cpp)
target_link_libraries(VerifiedChain PUBLIC Block)

add_library(Balances SHARED Balances.cpp)
target_link_libraries(Balances PUBLIC VerifiedChain)

add_library(BranchingChain SHARED BranchingChain.cpp)
target_link_libraries(BranchingChain PUBLIC Block)

add_library(BlockChain SHARED BlockChain.cpp)
target_link_libraries(BlockChain PUBLIC VerifiedChain BranchingChain)

add_library(User SHARED User.cpp)

add_executable(TESTER test.cpp)
target_link_libraries(TESTER BlockChain)

