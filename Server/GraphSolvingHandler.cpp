//
// Created by shani on 1/24/20.
//

#include "GraphSolvingHandler.h"

#include "DataReader.h"

namespace server_side {
    std::vector<graph::MatrixGraph::WeightT> GraphSolvingHandler::parseMatrixLine(const std::string &line) {
        constexpr auto SEPARATOR = ',';
        auto result = std::vector<graph::MatrixGraph::WeightT>{};

        auto begin = 0;
        while (true) {
            auto findPosition = line.find(SEPARATOR, begin);
            const auto size = findPosition == std::string::npos ? std::string::npos : findPosition - begin;
            result.push_back(std::stoll(line.substr(begin, size)));
            if (findPosition == std::string::npos) {
                break;
            }

            begin = findPosition + 1;
        }

        return result;
    }

    graph::MatrixGraph GraphSolvingHandler::parseMatrix(const std::string &matrix) {
        constexpr auto SEPARATOR = '\n';

        if (matrix.empty()) {
            return graph::MatrixGraph({}, 0, 0);
        }

        auto result = std::vector<graph::MatrixGraph::WeightT>{};
        auto matrixSize = std::size_t{0};

        auto begin = 0;
        while (true) {
            auto findPosition = matrix.find(SEPARATOR, begin);
            const auto size = findPosition == std::string::npos ? std::string::npos : findPosition - begin;
            auto parsedLine = parseMatrixLine(matrix.substr(begin, size));
            result.insert(result.end(), parsedLine.begin(), parsedLine.end());
            if (findPosition == std::string::npos) {
                matrixSize = parsedLine.size();
                break;
            }

            begin = findPosition + 1;
        }

        return {result, matrixSize, matrixSize};
    }

    std::tuple<graph::MatrixGraph, graph::MatrixGraph::Vertex, graph::MatrixGraph::Vertex>
    GraphSolvingHandler::parseClientData(std::string data) {
        // Remove the end and end of line
        data.resize(data.size() - 4);

        const auto secondEndline = data.rfind(ENDLINE_TOKEN);
        const auto firstEndline = data.rfind(ENDLINE_TOKEN, secondEndline - 1);

        return {
                parseMatrix(data.substr(0, firstEndline)),
                parseVertex(data.substr(firstEndline + 1, secondEndline - firstEndline + 1)),
                parseVertex(data.substr(secondEndline + 1))
        };
    }

    graph::MatrixGraph::Vertex GraphSolvingHandler::parseVertex(const std::string &line) {
        const auto splitPosition = line.find(SPLIT_TOKEN);
        return graph::MatrixGraph::Vertex{std::stoull(line.substr(0, splitPosition)),
                                          std::stoull(line.substr(splitPosition + 1))};
    }

    void GraphSolvingHandler::handleClient(utilities::sockets::TcpSocket sock) const {
        auto result = parseClientData(readClientData(sock));
        auto solution = m_solver->solve(std::get<0>(result), std::get<1>(result), std::get<2>(result));
        sock.send(solutionToString(std::move(solution)));
        sock.send("\n");
    }

    GraphSolvingHandler::GraphSolvingHandler(std::unique_ptr<graph::algorithms::Solver> solver) noexcept :
            m_solver(std::move(solver)) {
    }

    std::string GraphSolvingHandler::solutionToString(std::stack<graph::algorithms::Directions> solution) {
        if (solution.size() <= 1) {
            return std::string{};
        }

        std::string result{};
        while (solution.size() > 2) {
            result += graph::algorithms::toString(solution.top()) + ",";
            solution.pop();
        }
        result += graph::algorithms::toString(solution.top());

        return result;
    }
}
