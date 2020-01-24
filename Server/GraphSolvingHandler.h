//
// Created by shani on 1/24/20.
//

#include <memory>
#include <tuple>
#include <vector>

#include "ClientHandler.h"
#include "Graph/MatrixGraph.h"
#include "Graph/Algorithms/Solver.h"

namespace server_side {
    constexpr auto SPLIT_TOKEN = ',';

    class GraphSolvingHandler : public ClientHandler {
    public:
        explicit GraphSolvingHandler(std::unique_ptr<graph::algorithms::Solver> solver) noexcept;

        void handleClient(utilities::sockets::TcpSocket sock) const override;

    private:
        static std::tuple<graph::MatrixGraph, graph::MatrixGraph::Vertex, graph::MatrixGraph::Vertex>
        parseClientData(std::string data);

        static graph::MatrixGraph::Vertex parseVertex(const std::string &line);

        static std::vector<graph::MatrixGraph::WeightT> parseMatrixLine(const std::string &line);

        static graph::MatrixGraph parseMatrix(const std::string &matrix);

        static std::string solutionToString(std::stack<graph::algorithms::Directions> solution);

        std::unique_ptr<graph::algorithms::Solver> m_solver;
    };
}

