#include <iostream>
#include <cmath>

#include "Server/TcpServer.h"
#include "Server/GraphSolvingHandler.h"

#include "Graph/MatrixGraph.h"
#include "Graph/Algorithms/Dfs.h"
#include "Graph/Algorithms/Astar.h"
#include "Graph/Algorithms/Bfs.h"
#include "Graph/Algorithms/BestFS.h"

#include "Server/ParallelDispatcher.h"
#include "Server/SerialDispatcher.h"

int main() {
    try {
        auto tcpServer = server_side::sockets::TcpServer();
        tcpServer.open(8080);
        auto dispatcher = std::unique_ptr<server_side::Dispatcher>(new server_side::ParallelDispatcher{});
        dispatcher->dispatch(std::move(tcpServer),
                             std::unique_ptr<server_side::ClientHandler>(new server_side::GraphSolvingHandler{
                                     std::unique_ptr<graph::algorithms::Solver>(new graph::algorithms::AStar{})}));
    }
    catch (std::exception &e) {
        std::cout << "Program terminated with an exception: " << e.what() << std::endl;
    }
    return 0;
}
