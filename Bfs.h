//
// Created by shani on 1/24/20.
//

#pragma once

#include <vector>

// This class represents a directed graph using
// adjacency list representation
class Graph
{
public:

    virtual void addEdge(int v, int w) = 0;

    virtual bool areConnected(int v1, int v2) = 0;

    virtual ~Graph() = default;
};


