cmake_minimum_required(VERSION 3.5)

project(ZINA_QT LANGUAGES CXX)
include_directories(include)
include_directories(src)

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
target_link_libraries(Hash PUBLIC ssl crypto secp256k1)

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

#add_executable(TESTER blockchain_test.cpp)
#target_link_libraries(TESTER BlockChain)

#add_executable(USER_INTERFACE User_interface.cpp)
#target_link_libraries(USER_INTERFACE BlockChain User)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    UserInterface.cpp
    UserInterface.h
    UserInterface.ui
    addtransactiondialog.cpp
    addtransactiondialog.h
    addtransactiondialog.ui
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

target_link_libraries(ZINA_QT PRIVATE BlockChain User Qt${QT_VERSION_MAJOR}::Widgets)
