//
// Created by shani on 1/24/20.
//

#include "Bfs.h"

#include <map>
#include <queue>

namespace graph {
    namespace algorithms {
        std::stack<Directions> Bfs::BfsSolver::BFSUtil(const MatrixGraph::Vertex begin) {
            m_cameFrom[begin] = begin;
            m_visited[toArrayIndex(begin)] = true;

            std::queue<MatrixGraph::Vertex> nodesToExplore{};
            nodesToExplore.push(begin);

            while (!nodesToExplore.empty()) {
                const auto currentVertex = nodesToExplore.front();
                nodesToExplore.pop();

                if (currentVertex == m_end) {
                    break;
                }

                for (const auto nextVertex: m_matrix.getAllNeighbors(currentVertex)) {
                    const auto nextVertexIndex = toArrayIndex(nextVertex);
                    if (m_visited[nextVertexIndex]) {
                        continue;
                    }
                    m_visited[nextVertexIndex] = true;
                    m_cameFrom[nextVertex] = currentVertex;
                    nodesToExplore.push(nextVertex);
                }
            }

            return reconstructPath();
        }

        std::stack<Directions> Bfs::BfsSolver::solve() {
            return BFSUtil(m_begin);
        }

        size_t Bfs::BfsSolver::toArrayIndex(graph::MatrixGraph::Vertex vertex) const {
            return matrixIndexToArrayIndex(vertex.rowIndex, vertex.columnIndex, m_matrix.height(), m_matrix.width());
        }

        std::stack<Directions> graph::algorithms::Bfs::solve(const MatrixGraph& graph, MatrixGraph::Vertex begin, MatrixGraph::Vertex end) const {
            return BfsSolver(graph, begin, end).solve();
        }

        Bfs::BfsSolver::BfsSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin, MatrixGraph::Vertex end)
                : m_matrix(matrix), m_begin(begin), m_end(end), m_visited(matrix.height() * matrix.width(), false) {

        }

        std::stack<Directions> Bfs::BfsSolver::reconstructPath() {
            std::stack<Directions> path;
            path.push(Directions::NULL_MOVE);

            auto currentVertex = m_end;
            while (!(m_cameFrom.at(currentVertex) == currentVertex)) {
                path.push(getDirectionUnsafe(m_cameFrom.at(currentVertex), currentVertex));
                currentVertex = m_cameFrom[currentVertex];
            }

            return path;
        }

    }
}
