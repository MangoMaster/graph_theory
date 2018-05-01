#include <iostream>
#include "func.h"

using namespace std;

void graph_trans::forward_edge()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = forward_table[0][i]; j < forward_table[0][i + 1]; j++)
        {
            edge_list[0].push_back(i);
            edge_list[1].push_back(forward_table[1][j]);
            edge_list[2].push_back(forward_table[2][j]);
        }
    }
}