makefile_directory := $(abspath .)

default_target: all
.PHONY: all

all:
	g++ -I $(makefile_directory) main.cpp Socket/TcpSocket.cpp Server/TcpServer.cpp Graph/Algorithms/Dfs.cpp Graph/Algorithms/Bfs.cpp Graph/Algorithms/Astar.cpp Graph/MatrixGraph.cpp Graph/Algorithms/Utilities.cpp Server/GraphSolvingHandler.cpp Server/DataReader.cpp Graph/Algorithms/BestFS.cpp Server/ParallelDispatcher.cpp Server/SerialDispatcher.cpp -std=c++11 -lpthread
