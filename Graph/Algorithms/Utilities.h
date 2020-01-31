//
// Created by shani on 1/24/20.
//

#pragma once

#include <stdexcept>

#include "Graph/MatrixGraph.h"

namespace std
{
    template<>
    struct less<graph::MatrixGraph::Vertex>
    {
        bool operator()(graph::MatrixGraph::Vertex lhs, graph::MatrixGraph::Vertex rhs) const;
    };

}

namespace graph {
    namespace algorithms {
        enum class Directions {
            UP, DOWN, LEFT, RIGHT, NULL_MOVE
        };

        std::string toString(Directions direction);

        std::size_t matrixIndexToArrayIndex(std::size_t rowIndex, std::size_t columnIndex,
                                            std::size_t height, std::size_t width);

        /**
         * This function does not validate input.
         * @param from source vertex
         * @param to target vertex
         * @return the moving direction from source to target. The function
         *  results in an arbitrary output for vertices that are not neighbors
         *  in the graph.
         */
        Directions getDirectionUnsafe(MatrixGraph::Vertex from, MatrixGraph::Vertex to) noexcept;
    }
}
