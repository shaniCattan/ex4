cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex4 main.cpp Server/Server.h Server/ClientHandler.h Socket/TcpSocket.cpp Socket/TcpSocket.h
        Server/TcpServer.cpp Server/TcpServer.h  Hillclimbing.cpp Graph/Algorithms/Dfs.cpp Bfs.cpp Astar.cpp Graph/MatrixGraph.cpp Graph/MatrixGraph.h Graph/Algorithms/Utilities.h Graph/Algorithms/Solver.h Graph/Algorithms/Utilities.cpp Server/GraphSolvingHandler.cpp Server/GraphSolvingHandler.h Server/DataReader.h Server/DataReader.cpp)
target_include_directories(ex4 PRIVATE .)

