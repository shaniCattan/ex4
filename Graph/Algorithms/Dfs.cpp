//
// Created by shani on 1/24/20.
//

#include "Dfs.h"

// C++ program to print DFS traversal from
// a given vertex in a  given graph
#include<iostream>
#include<list>


namespace graph {
    namespace algorithms {
        std::stack<Directions> Dfs::DfsSolver::DFSUtil(MatrixGraph::Vertex vertex) {

            const auto vertexIndex = toArrayIndex(vertex);
            if (m_visited[vertexIndex]) {
                return {};
            }

            auto resultPath = std::stack<Directions>{};

            // Mark the current node as visited
            m_visited[vertexIndex] = true;

            // GO DOWN
            ++vertex.rowIndex;
            resultPath = DFSUtil(vertex);
            if (!resultPath.empty()) {
                resultPath.push(Directions::DOWN);
            }

            // GO RIGHT
            --vertex.rowIndex;
            ++vertex.columnIndex;
            resultPath = DFSUtil(vertex);
            if (!resultPath.empty()) {
                resultPath.push(Directions::RIGHT);
            }

            // GO UP
            --vertex.rowIndex;
            --vertex.columnIndex;
            resultPath = DFSUtil(vertex);
            if (!resultPath.empty()) {
                resultPath.push(Directions::UP);
            }

            // GO LEFT
            ++vertex.rowIndex;
            --vertex.columnIndex;
            DFSUtil(vertex);
            if (!resultPath.empty()) {
                resultPath.push(Directions::LEFT);
            }

            return {};
        }

        std::stack<Directions> Dfs::DfsSolver::solve() {
            return DFSUtil(m_begin);
        }

        size_t Dfs::DfsSolver::toArrayIndex(graph::MatrixGraph::Vertex vertex) const {
            return matrixIndexToArrayIndex(vertex.rowIndex, vertex.columnIndex, m_matrix.height(), m_matrix.width());
        }

        std::stack<Directions> graph::algorithms::Dfs::solve(const graph::MatrixGraph &matrix) const {
            return DfsSolver(matrix, {0, 0}, {matrix.height() - 1, matrix.width() - 1}).solve();
        }

        Dfs::DfsSolver::DfsSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin, MatrixGraph::Vertex end)
                : m_matrix(matrix), m_begin(begin), m_end(end), m_visited(matrix.height() * matrix.width(), false) {

        }

    }
}
