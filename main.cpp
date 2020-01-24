#include <iostream>
#include <cmath>

#include "Server/TcpServer.h"
#include "Server/GraphSolvingHandler.h"

#include "Graph/MatrixGraph.h"
#include "Graph/Algorithms/Dfs.h"
#include "Graph/Algorithms/Astar.h"

int main() {
    try {
        auto tcpServer = server_side::sockets::TcpServer();
        tcpServer.open(8080);
        auto client = tcpServer.accept();
        auto clientHandle = server_side::GraphSolvingHandler(
                std::unique_ptr<graph::algorithms::Solver>(new graph::algorithms::AStar{})
                );
        clientHandle.handleClient(std::move(client));
    }
    catch (std::exception &e) {
        std::cout << "Program terminated with an exception: " << e.what() << std::endl;
    }
    return 0;
}
