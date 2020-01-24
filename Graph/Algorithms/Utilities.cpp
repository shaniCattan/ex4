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
    }
}
