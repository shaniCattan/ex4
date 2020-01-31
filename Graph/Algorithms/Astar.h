//
// Created by shani on 1/24/20.
//

#pragma once

#include <map>

#include "Solver.h"


namespace graph {
    namespace algorithms {
        class AStar : public Solver {
            class AStarSolver final {
                using Vertex = graph::MatrixGraph::Vertex;
                constexpr static auto INF_VALUE = static_cast<size_t>(-1);
            public:
                AStarSolver(const MatrixGraph &matrix, MatrixGraph::Vertex begin,
                          MatrixGraph::Vertex end);

                std::stack<Directions> solve();

                std::size_t heuristic(MatrixGraph::Vertex vertex) const;
            private:
                std::stack<Directions> reconstructPath() const;

                const MatrixGraph::Vertex m_begin;
                const MatrixGraph::Vertex m_end;
                const MatrixGraph &m_matrix;

                std::map<graph::MatrixGraph::Vertex, graph::MatrixGraph::Vertex> m_successors;
            };

        public:
            std::stack<Directions> solve(const MatrixGraph& graph, MatrixGraph::Vertex begin, MatrixGraph::Vertex end) const override;
        };
    }
}
