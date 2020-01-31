//
// Created by shani on 1/24/20.
//

#pragma once

#include <map>

#include "Solver.h"


namespace graph {
    namespace algorithms {
        class BestFS : public Solver {
            class BestFSSolver final {
                using Vertex = graph::MatrixGraph::Vertex;
                constexpr static auto INF_VALUE = static_cast<size_t>(-1);
            public:
                BestFSSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin,
                            MatrixGraph::Vertex end);

                std::stack<Directions> solve();
            private:

                std::stack<Directions> reconstructPath() const;

                const MatrixGraph::Vertex m_begin;
                const MatrixGraph::Vertex m_end;
                const MatrixGraph &m_matrix;

                std::map<MatrixGraph::Vertex, MatrixGraph::Vertex> m_cameFrom;
            };

        public:
            std::stack<Directions> solve(const MatrixGraph& graph, MatrixGraph::Vertex begin, MatrixGraph::Vertex end) const override;
        };
    }
}
