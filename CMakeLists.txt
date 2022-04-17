cmake_minimum_required(VERSION 3.18)
project(ZINA_Blockchain)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Weffc++ -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Waggressive-loop-optimizations -Walloc-zero -Walloca -Walloca-larger-than=8192 -Warray-bounds -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlarger-than=8192 -Wvla-larger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wrestrict -Wshadow -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wnarrowing -Wno-old-style-cast -Wvarargs -Waligned-new -Walloc-size-larger-than=1073741824 -Walloc-zero -Walloca -Walloca-larger-than=8192 -Wcast-align=strict -Wdangling-else -Wduplicated-branches -Wformat-overflow=2 -Wformat-truncation=2 -Wmissing-attributes -Wmultistatement-macros -Wrestrict -Wshadow=global -Wsuggest-attribute=malloc -fcheck-new -fsized-deallocation -fstack-check -fstrict-overflow -fchkp-first-field-has-own-bounds -fchkp-narrow-to-innermost-array -flto-odr-type-merging -fno-omit-frame-pointer")
set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LOCAL_JUDGE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")


set(CMAKE_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(ZINA SHARED ZINA.cpp)
add_library(Hash SHARED Hash.cpp)
target_link_libraries(Hash PUBLIC ssl crypto secp256k1 boost_thread)

add_library(definitions SHARED definitions.cpp)
target_link_libraries(definitions PUBLIC ZINA Hash)

add_library(constants SHARED constants.cpp)
target_link_libraries(constants PUBLIC definitions)

add_library(Transaction SHARED Transaction.cpp)
target_link_libraries(Transaction PUBLIC constants)

add_library(Coinbase SHARED Coinbase.cpp)
target_link_libraries(Coinbase PUBLIC constants)

add_library(Block SHARED Block.cpp)
target_link_libraries(Block PUBLIC Coinbase Transaction)

add_library(hash_functions SHARED hash_functions.cpp)
target_link_libraries(hash_functions PUBLIC Block constants)

add_library(VerifiedChain SHARED VerifiedChain.cpp)
target_link_libraries(VerifiedChain PUBLIC Block)

add_library(Balances SHARED Balances.cpp)
target_link_libraries(Balances PUBLIC VerifiedChain)

add_library(BranchingChain SHARED BranchingChain.cpp)
target_link_libraries(BranchingChain PUBLIC Block)

add_library(BlockChain SHARED BlockChain.cpp)
target_link_libraries(BlockChain PUBLIC VerifiedChain BranchingChain)

add_library(User SHARED User.cpp)

add_library(CPKey SHARED  CPKey.cpp)
target_link_libraries(User PUBLIC CPKey)

add_executable(TESTER blockchain_test.cpp)
target_link_libraries(TESTER BlockChain)

add_executable(USER_INTERFACE User_interface.cpp)
target_link_libraries(USER_INTERFACE BlockChain User)

add_library(Miner SHARED Miner.cpp)
target_link_libraries(Miner Block BlockChain Coinbase)

add_executable(MAIN main.cpp)
target_link_libraries(MAIN BlockChain User Miner)
