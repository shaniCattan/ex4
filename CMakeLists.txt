cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex4 main.cpp Server/Server.cpp Server/Server.h Server/ClientHandler.cpp Server/ClientHandler.h Socket/TcpSocket.cpp Socket/TcpSocket.h)
target_include_directories(ex4 PRIVATE .)
