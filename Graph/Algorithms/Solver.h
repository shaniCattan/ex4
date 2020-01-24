//
// Created by shani on 1/24/20.
//

#pragma once

#include <stack>

#include "Graph/MatrixGraph.h"
#include "Utilities.h"

namespace graph {
    namespace algorithms{
        class Solver {
        public:
            virtual std::stack<Directions> solve(const MatrixGraph& graph) const = 0;
        };

    }
}