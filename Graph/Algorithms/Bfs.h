//
// Created by shani on 1/24/20.
//

#pragma once

#include "Solver.h"

#include <map>

namespace graph {
    namespace algorithms {
        class Bfs : public Solver {
            class BfsSolver final {
            public:
                BfsSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin,
                          MatrixGraph::Vertex end);

                std::stack<Directions> solve();

            private:
                std::stack<Directions> BFSUtil(MatrixGraph::Vertex begin);
                std::size_t toArrayIndex(MatrixGraph::Vertex vertex) const;

                std::stack<Directions> reconstructPath();

                const MatrixGraph::Vertex m_begin;
                const MatrixGraph::Vertex m_end;
                const MatrixGraph &m_matrix;

                std::vector<bool> m_visited;
                std::map<MatrixGraph::Vertex, MatrixGraph::Vertex> m_cameFrom;
            };

        public:
            std::stack<Directions> solve(const MatrixGraph& graph, MatrixGraph::Vertex begin, MatrixGraph::Vertex end) const override;
        };
    }
}

