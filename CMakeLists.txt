cmake_minimum_required(VERSION 3.18)
project(ZINA_Blockchain)

set(CMAKE_CXX_STANDARD 14)


#add_library(Transaction SHARED Transaction.h)

#add_library(Coinbase SHARED Coinbase.h)

#target_link_libraries(Block.cpp Transaction)
#target_link_libraries(Block.cpp Coinbase)
add_library(Block SHARED Block.cpp)

add_library(hash_functions SHARED hash_functions.cpp)
target_link_libraries(hash_functions PUBLIC Block ssl crypto)

add_library(BranchingChain SHARED BranchingChain.cpp)
target_link_libraries(BranchingChain PUBLIC Block)

add_library(VerifiedChain SHARED VerifiedChain.cpp)
target_link_libraries(VerifiedChain PUBLIC Block)

add_library(BlockChain SHARED BlockChain.cpp)
target_link_libraries(BlockChain PUBLIC VerifiedChain BranchingChain)

add_executable(TESTER test.cpp)
target_link_libraries(TESTER BlockChain)
