#include "Utilities.h"

namespace graph {
    namespace algorithms {
        std::size_t matrixIndexToArrayIndex(const std::size_t rowIndex, const std::size_t columnIndex,
                                            const std::size_t height, const std::size_t width) {
            if (rowIndex >= height || columnIndex >= width) {
                throw std::invalid_argument{"Matrix indices out of bound"};
            }

            return rowIndex * width + columnIndex;
        }

        std::string toString(Directions direction) {
            switch (direction) {
                case graph::algorithms::Directions::UP:
                    return "Up";
                case graph::algorithms::Directions::DOWN:
                    return "Down";
                case graph::algorithms::Directions::RIGHT:
                    return "Right";
                case graph::algorithms::Directions::LEFT:
                    return "Left";
                default:
                    return "";
            }
        }

        Directions getDirectionUnsafe(MatrixGraph::Vertex from, MatrixGraph::Vertex to) noexcept {
            if (from.columnIndex < to.columnIndex) {
                return Directions::RIGHT;
            }

            if (from.columnIndex > to.columnIndex) {
                return Directions::LEFT;
            }

            if (from.rowIndex < to.rowIndex) {
                return Directions::DOWN;
            }

            return Directions::UP;
        }
    }
}
