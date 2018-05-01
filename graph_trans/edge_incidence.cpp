#include <iostream>
#include "func.h"

using namespace std;

void graph_trans::edge_incidence()
{
    for (int i = 0; i < m; i++)
    {
        incidence_matrix[edge_list[0][i]].push_back(1);
        incidence_matrix[edge_list[1][i]].push_back(-1);
        for (int j = 0; j < n; j++)
        {
            if (j != edge_list[0][i] && j != edge_list[1][i])
                incidence_matrix[j].push_back(0);
        }
    }
}