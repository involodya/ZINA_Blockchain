cmake_minimum_required(VERSION 3.5)

project(ZINA_QT LANGUAGES CXX)

include_directories(include)
#include_directories(src)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Weffc++ -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Waggressive-loop-optimizations -Walloc-zero -Walloca -Walloca-larger-than=8192 -Warray-bounds -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline -Wlarger-than=8192 -Wvla-larger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wrestrict -Wshadow -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wnarrowing -Wno-old-style-cast -Wvarargs -Waligned-new -Walloc-size-larger-than=1073741824 -Walloc-zero -Walloca -Walloca-larger-than=8192 -Wcast-align=strict -Wdangling-else -Wduplicated-branches -Wformat-overflow=2 -Wformat-truncation=2 -Wmissing-attributes -Wmultistatement-macros -Wrestrict -Wshadow=global -Wsuggest-attribute=malloc -fcheck-new -fsized-deallocation -fstack-check -fstrict-overflow -fchkp-first-field-has-own-bounds -fchkp-narrow-to-innermost-array -flto-odr-type-merging -fno-omit-frame-pointer")
set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(CMAKE_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


add_library(ZINA SHARED ZINA.cpp)
add_library(Hash SHARED Hash.cpp)
target_link_libraries(Hash PUBLIC ssl crypto secp256k1 boost_serialization)

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

add_library(VerifiedChain SHARED VerifiedChain.cpp)
target_link_libraries(VerifiedChain PUBLIC Block)

add_library(Balances SHARED Balances.cpp)
target_link_libraries(Balances PUBLIC VerifiedChain)

add_library(BranchingChain SHARED BranchingChain.cpp)
target_link_libraries(BranchingChain PUBLIC Block)

add_library(BlockChain SHARED BlockChain.cpp)
target_link_libraries(BlockChain PUBLIC VerifiedChain BranchingChain)

add_library(User SHARED User.cpp)

add_library(CPKey SHARED CPKey.cpp)
target_link_libraries(User PUBLIC CPKey)

add_library(Miner SHARED Miner.cpp)
target_link_libraries(Miner Block BlockChain Coinbase)

add_library(Serialization SHARED serialization_boost.cpp)
target_link_libraries(Serialization Block BlockChain Transaction User)

add_executable(USER_TEST user_tests.cpp)
target_link_libraries(USER_TEST BlockChain User Miner)

# add_executable(SERIALIZATION_TEST serialization_test.cpp)
# target_link_libraries(SERIALIZATION_TEST Serialization)

#add_executable(TESTER blockchain_test.cpp)
#target_link_libraries(TESTER BlockChain)

#add_executable(USER_INTERFACE User_interface.cpp)
#target_link_libraries(USER_INTERFACE BlockChain User)

find_package(QT NAMES Qt${QT_VERSION_MAJOR} Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    UserInterface.cpp
    UserInterface.h
    UserInterface.ui
    addtransactiondialog.cpp
    addtransactiondialog.h
    addtransactiondialog.ui
    confirmationwindow.cpp
    confirmationwindow.h
    confirmationwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ZINA_QT
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ZINA_QT SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ZINA_QT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ZINA_QT PRIVATE BlockChain Balances User Qt${QT_VERSION_MAJOR}::Widgets)


find_package(QT NAMES Qt${QT_VERSION_MAJOR} Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Network REQUIRED)

set(PROJECT_SOURCES
        network_tests.cpp
        networkwindow.cpp
        networkwindow.h
        networkwindow.ui
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NETWORK
            ${PROJECT_SOURCES}
            )
else ()
    if (ANDROID)
        add_library(NETWORK SHARED
                ${PROJECT_SOURCES}
                )
    else ()
        add_executable(NETWORK
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

target_link_libraries(NETWORK PRIVATE Miner Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
