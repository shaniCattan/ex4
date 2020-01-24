//
// Created by shani on 1/24/20.
//

#pragma once

#include "Solver.h"

namespace graph {
    namespace algorithms {
        class Dfs : public Solver {
            class DfsSolver final {
            public:
                DfsSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin,
                          MatrixGraph::Vertex end);

                std::stack<Directions> solve();

            private:
                std::stack<Directions> DFSUtil(MatrixGraph::Vertex vertex);
                std::size_t toArrayIndex(MatrixGraph::Vertex vertex) const;

                const MatrixGraph::Vertex m_begin;
                const MatrixGraph::Vertex m_end;
                const MatrixGraph &m_matrix;

                std::vector<bool> m_visited;
            };

        public:
            std::stack<Directions> solve(const MatrixGraph &matrix) const override;
        };
    }
}

