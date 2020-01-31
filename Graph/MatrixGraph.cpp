//
// Created by shani on 1/24/20.
//

#include <algorithm>
#include <stdexcept>

#include "MatrixGraph.h"

namespace graph {

    MatrixGraph::MatrixGraph(std::vector<WeightT> weights, std::size_t height, std::size_t width)
            : m_weights(std::move(weights)), m_height(height), m_width(width) {
        if (m_weights.size() != m_height * m_width) {
            throw std::invalid_argument{"Width and size don't match to the weights matrix"};
        }
    }

    MatrixGraph::WeightT MatrixGraph::getWeight(const Vertex& vertex) const {
        if (!isVertexValid(vertex)) {
            // TODO explain
            throw std::invalid_argument{"Got an invalid vertex"};
        }

        return m_weights[indexOf(vertex)];
    }

    std::vector<MatrixGraph::Vertex> MatrixGraph::getAllNeighbors(MatrixGraph::Vertex vertex) const {
        auto vector = std::vector<MatrixGraph::Vertex>(4, vertex);
        --vector[0].rowIndex;
        ++vector[1].rowIndex;
        --vector[2].columnIndex;
        ++vector[3].columnIndex;

        vector.erase(std::remove_if(vector.begin(), vector.end(), [this](const MatrixGraph::Vertex vertex) {
            return !isVertexValid(vertex);
        }), vector.end());

        return vector;
    }


    bool MatrixGraph::isVertexValid(const MatrixGraph::Vertex &vertex) const {
        return m_height > vertex.rowIndex && m_width > vertex.columnIndex;
    }

    std::size_t MatrixGraph::indexOf(const MatrixGraph::Vertex &vertex) const {
        return vertex.rowIndex * m_width + vertex.columnIndex;
    }

    std::size_t MatrixGraph::height() const {
        return m_height;
    }

    std::size_t  MatrixGraph::width() const {
        return m_width;
    }

}