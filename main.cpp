#include <iostream>
#include <cmath>

#include "Server/TcpServer.h"

#include "Graph/MatrixGraph.h"
#include "Graph/Algorithms/Dfs.h"

std::string readMatrixFromClient(const utilities::sockets::TcpSocket &socket) {
    auto buffer = std::string{};
    while (buffer.find("end") == std::string::npos) {
        buffer += socket.readAtMost(1024);
    }

    if (buffer.size() >= 4) {
        buffer.resize(buffer.size() - 4);
    }
    return buffer;
}

std::vector<graph::MatrixGraph::WeightT> parseLine(const std::string &line) {
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

std::vector<graph::MatrixGraph::WeightT> parseMatrix(const std::string &matrix) {
    constexpr auto SEPARATOR = '\n';

    if (matrix.empty()) {
        return {};
    }

    auto result = std::vector<graph::MatrixGraph::WeightT>{};

    auto begin = 0;
    while (true) {
        auto findPosition = matrix.find(SEPARATOR, begin);
        const auto size = findPosition == std::string::npos ? std::string::npos : findPosition - begin;
        auto parsedLine = parseLine(matrix.substr(begin, size));
        result.insert(result.end(), parsedLine.begin(), parsedLine.end());
        if (findPosition == std::string::npos) {
            break;
        }

        begin = findPosition + 1;
    }

    return result;
}

int main() {
    try {
        auto tcpServer = server_side::sockets::TcpServer();
        tcpServer.open(8080);
        auto client = tcpServer.accept();
        auto buffer = readMatrixFromClient(client);
        auto weights = parseMatrix(buffer);
        const auto matrixSize = static_cast<std::size_t>(std::sqrt(weights.size()));
        const auto matrix = graph::MatrixGraph{std::move(weights),
                                               matrixSize, matrixSize};
        const auto dfs = graph::algorithms::Dfs{};
        auto result = dfs.solve(matrix);

        while (!result.empty()) {
            switch (result.top()) {
                case graph::algorithms::Directions::LEFT:
                    client.send("Left");
                    break;
                case graph::algorithms::Directions::RIGHT:
                    client.send("Right");
                    break;
                case graph::algorithms::Directions::UP:
                    client.send("Up");
                    break;
                case graph::algorithms::Directions::DOWN:
                    client.send("Down");
                    break;
                case graph::algorithms::Directions::NULL_MOVE:
                    client.send("\n");
                    break;
            }
            result.pop();
            if (result.size() > 1) {
                client.send(",");
            }
        }
    }
    catch (std::exception &e) {
        std::cout << "Program terminated with an exception: " << e.what() << std::endl;
    }
    return 0;
}
