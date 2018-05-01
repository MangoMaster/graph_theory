#include <iostream>
#include "func.h"

using namespace std;

graph_trans::graph_trans()
{
    n = 0;
    m = 0;

    load();

    incidence_matrix.resize(n);
    for (int i = 0; i < n; i++)
    {
        incidence_matrix[i].reserve(m);
    }

    edge_list.resize(3);
    for (int i = 0; i < 3; i++)
    {
        edge_list[i].reserve(m);
    }

    forward_table.resize(3);
    forward_table[0].resize(n + 1);
    for (int i = 1; i < 3; i++)
    {
        forward_table[i].reserve(m);
    }

    adjacency_table.resize(n, nullptr);
}