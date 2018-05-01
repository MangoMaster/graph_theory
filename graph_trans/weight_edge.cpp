#include <iostream>
#include "func.h"

using namespace std;

void graph_trans::weight_edge()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (weight_matrix[i][j] != 0)
            {
                edge_list[0].push_back(i);
                edge_list[1].push_back(j);
                edge_list[2].push_back(weight_matrix[i][j]);
            }
        }
    }
}