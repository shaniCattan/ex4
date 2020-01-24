//
// Created by shani on 1/24/20.
//

#include <tuple>
#include <vector>

#include "ClientHandler.h"
#include "Graph/MatrixGraph.h"

namespace server_side {
    constexpr auto SPLIT_TOKEN = ',';

    class GraphSolvingHandler : public ClientHandler {
    public:
        void handleClient(utilities::sockets::TcpSocket sock) const override;
    private:
        static std::tuple<graph::MatrixGraph, graph::MatrixGraph::Vertex, graph::MatrixGraph::Vertex>
                parseClientData(std::string data);

        static graph::MatrixGraph::Vertex parseVertex(const std::string& line);

        static std::vector<graph::MatrixGraph::WeightT> parseMatrixLine(const std::string &line);

        static graph::MatrixGraph parseMatrix(const std::string &matrix);
    };
}

