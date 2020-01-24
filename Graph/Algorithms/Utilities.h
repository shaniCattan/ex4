//
// Created by shani on 1/24/20.
//

#pragma once

#include <stdexcept>

namespace graph {
    namespace algorithms {
        enum class Directions {
            UP, DOWN, LEFT, RIGHT, NULL_MOVE
        };

        std::string toString(Directions direction);

        std::size_t matrixIndexToArrayIndex(std::size_t rowIndex, std::size_t columnIndex,
                                            std::size_t height, std::size_t width);
    }
}
