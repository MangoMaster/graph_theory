#include <iostream>
#include "func.h"

using namespace std;

void graph_trans::weight_adjacency()
{
    for (int i = 0; i < n; i++)
    {
        adjacency_node **pnode = &adjacency_table[i];
        for (int j = 0; j < n; j++)
        {
            if (weight_matrix[i][j] != 0)
            {
                *pnode = new adjacency_node;
                (*pnode)->terminal = j;
                (*pnode)->weight = weight_matrix[i][j];
                (*pnode)->next = nullptr;
                pnode = &((*pnode)->next);
            }
        }
    }
}