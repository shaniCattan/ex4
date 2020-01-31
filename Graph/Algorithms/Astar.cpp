//
// Created by shani on 1/24/20.
//

#include "Astar.h"

#include <algorithm>
#include <set>


namespace graph {
    namespace algorithms {

        std::stack<Directions> AStar::AStarSolver::solve() {
            auto openList = std::set<Vertex>{};
            openList.insert(m_begin);

            auto realCost = std::map<Vertex, std::size_t>{};
            realCost[m_begin] = 0;

            const auto getRealCost = [&realCost](const Vertex vertex) {
                if (realCost.count(vertex)) {
                    return realCost[vertex];
                }

                return INF_VALUE;
            };

            const auto getFScore = [this, &getRealCost](const Vertex vertex) {
                return heuristic(vertex) + getRealCost(vertex);
            };

            while (!openList.empty()) {
                const auto currentNode =
                        *std::min_element(openList.begin(), openList.end(),
                                          [&](const Vertex lhs, const Vertex rhs) {
                                              return getFScore(lhs) < getFScore(rhs);
                                          });
                openList.erase(currentNode);
                if (currentNode == m_end) {
                    break;
                }

                const auto successorRealCost = getRealCost(currentNode);

                for (auto neighbor: m_matrix.getAllNeighbors(currentNode)) {
                    const auto tentativeRealCost = successorRealCost + m_matrix.getWeight(neighbor);
                    if (tentativeRealCost < getRealCost(neighbor)) {
                        m_successors[neighbor] = currentNode;
                        realCost[neighbor] = tentativeRealCost;
                        if (!openList.count(neighbor)) {
                            openList.insert(neighbor);
                        }
                    }
                }
            }
            return reconstructPath();
        }

        std::stack<Directions> graph::algorithms::AStar::solve(const MatrixGraph &graph, MatrixGraph::Vertex begin,
                                                               MatrixGraph::Vertex end) const {
            return AStarSolver(graph, begin, end).solve();
        }

        AStar::AStarSolver::AStarSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin, MatrixGraph::Vertex end)
                : m_matrix(matrix), m_begin(begin), m_end(end) {

        }

        std::size_t AStar::AStarSolver::heuristic(MatrixGraph::Vertex vertex) const {
            return m_matrix.getWeight(vertex) + std::llabs(
                    static_cast<std::int64_t>(vertex.columnIndex) - static_cast<std::int64_t>(m_end.columnIndex)) +
                   std::llabs(static_cast<std::int64_t>(vertex.rowIndex) - static_cast<std::int64_t>(m_end.rowIndex));
        }

        std::stack<Directions> AStar::AStarSolver::reconstructPath() const {
            auto result = std::stack<Directions>{};
            result.push(Directions::NULL_MOVE);

            auto currentNode = m_end;
            while (!(currentNode == m_begin)) {
                result.push(getDirectionUnsafe(m_successors.at(currentNode), currentNode));
                currentNode = m_successors.at(currentNode);
            }

            return result;
        }

    }
}
