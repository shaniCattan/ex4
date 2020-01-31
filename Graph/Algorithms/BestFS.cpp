//
// Created by shani on 1/24/20.
//

#include "BestFS.h"

#include <algorithm>
#include <vector>

namespace graph {
    namespace algorithms {

        std::stack<Directions> BestFS::BestFSSolver::solve() {
            m_cameFrom[m_begin] = m_begin;

            auto realCost = std::map<Vertex, std::size_t>{};
            realCost[m_begin] = 0;

            const auto getRealCost = [&realCost](const Vertex vertex) {
                if (realCost.count(vertex)) {
                    return realCost[vertex];
                }

                return INF_VALUE;
            };

            const auto getScore = [this, &getRealCost](const Vertex vertex) {
                return getRealCost(vertex);
            };


            std::vector<MatrixGraph::Vertex> nodesToExplore{};
            nodesToExplore.push_back(m_begin);

            while (!nodesToExplore.empty()) {
                const auto currentVertexIter = std::min_element(
                        nodesToExplore.begin(), nodesToExplore.end(),
                        [&](const Vertex lhs, const Vertex rhs) {
                            return getScore(lhs) < getScore(rhs);
                        });
                const auto currentVertex = *currentVertexIter;
                nodesToExplore.erase(currentVertexIter);

                if (currentVertex == m_end) {
                    break;
                }

                for (const auto nextVertex: m_matrix.getAllNeighbors(currentVertex)) {
                    const auto tentativePrice = getScore(currentVertex) + m_matrix.getWeight(nextVertex);
                    if (getRealCost(nextVertex) <= tentativePrice) {
                        continue;
                    }
                    realCost[nextVertex] = tentativePrice;
                    m_cameFrom[nextVertex] = currentVertex;
                    nodesToExplore.push_back(nextVertex);
                }
            }

            return reconstructPath();
        }

        std::stack<Directions> graph::algorithms::BestFS::solve(const MatrixGraph &graph, MatrixGraph::Vertex begin,
                                                               MatrixGraph::Vertex end) const {
            return BestFSSolver(graph, begin, end).solve();
        }

        BestFS::BestFSSolver::BestFSSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin, MatrixGraph::Vertex end)
                : m_matrix(matrix), m_begin(begin), m_end(end) {

        }

        std::stack<Directions> BestFS::BestFSSolver::reconstructPath() const {
            auto result = std::stack<Directions>{};
            result.push(Directions::NULL_MOVE);

            auto currentNode = m_end;
            while (!(currentNode == m_begin)) {
                result.push(getDirectionUnsafe(m_cameFrom.at(currentNode), currentNode));
                currentNode = m_cameFrom.at(currentNode);
            }

            return result;
        }

    }
}
