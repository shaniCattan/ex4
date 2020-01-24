//
// Created by shani on 1/24/20.
//

#pragma once

#include <vector>

namespace graph {

    class MatrixGraph {
    public:
        struct Vertex {
            std::size_t rowIndex;
            std::size_t columnIndex;

            bool operator==(const Vertex &vertex) const {
                return rowIndex == vertex.rowIndex && columnIndex == vertex.columnIndex;
            }
        };

        using WeightT = std::size_t;
        constexpr static auto INFINITE_WEIGHT = static_cast<WeightT>(-1);

        MatrixGraph(std::vector<WeightT> weights, std::size_t height, std::size_t width);

        WeightT getWeight(const Vertex &vertex) const;

        bool isVertexValid(const Vertex &vertex) const;

        std::size_t height() const;

        std::size_t width() const;

    private:
        std::size_t indexOf(const Vertex &vertex) const;

        std::vector<WeightT> m_weights;
        std::size_t m_height;
        std::size_t m_width;
    };

}
