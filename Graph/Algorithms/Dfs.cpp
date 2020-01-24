//
// Created by shani on 1/24/20.
//

#include "Dfs.h"

namespace graph {
    namespace algorithms {
        std::stack<Directions> Dfs::DfsSolver::DFSUtil(MatrixGraph::Vertex vertex) {
            if (!m_matrix.isVertexValid(vertex)) {
                return {};
            }

            const auto vertexIndex = toArrayIndex(vertex);
            if (m_visited[vertexIndex]) {
                return {};
            }

            if (m_end == vertex) {
                auto stack = std::stack<Directions>{};
                stack.push(Directions::NULL_MOVE);
                return stack;
            }

            auto resultPath = std::stack<Directions>{};

            // Mark the current node as visited
            m_visited[vertexIndex] = true;

            // GO DOWN
            ++vertex.rowIndex;
            resultPath = DFSUtil(vertex);
            if (!resultPath.empty()) {
                resultPath.push(Directions::DOWN);
                return resultPath;
            }

            // GO RIGHT
            --vertex.rowIndex;
            ++vertex.columnIndex;
            resultPath = DFSUtil(vertex);
            if (!resultPath.empty()) {
                resultPath.push(Directions::RIGHT);
                return resultPath;
            }

            // GO UP
            --vertex.rowIndex;
            --vertex.columnIndex;
            resultPath = DFSUtil(vertex);
            if (!resultPath.empty()) {
                resultPath.push(Directions::UP);
                return resultPath;
            }

            // GO LEFT
            ++vertex.rowIndex;
            --vertex.columnIndex;
            DFSUtil(vertex);
            if (!resultPath.empty()) {
                resultPath.push(Directions::LEFT);
                return resultPath;
            }

            return {};
        }

        std::stack<Directions> Dfs::DfsSolver::solve() {
            return DFSUtil(m_begin);
        }

        size_t Dfs::DfsSolver::toArrayIndex(graph::MatrixGraph::Vertex vertex) const {
            return matrixIndexToArrayIndex(vertex.rowIndex, vertex.columnIndex, m_matrix.height(), m_matrix.width());
        }

        std::stack<Directions> graph::algorithms::Dfs::solve(const MatrixGraph& graph, MatrixGraph::Vertex begin, MatrixGraph::Vertex end) const {
            return DfsSolver(graph, begin, end).solve();
        }

        Dfs::DfsSolver::DfsSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin, MatrixGraph::Vertex end)
                : m_matrix(matrix), m_begin(begin), m_end(end), m_visited(matrix.height() * matrix.width(), false) {

        }

    }
}
