cmake_minimum_required(VERSION 3.14)

project(rc522 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(pimfrc522 STATIC
    rfid/src/MFRC522.cpp
    
#   Doesn't compile right now...
#   rfid/src/MFRC522Extended.cpp
    )

target_link_libraries(pimfrc522 pigpiod_if2)
