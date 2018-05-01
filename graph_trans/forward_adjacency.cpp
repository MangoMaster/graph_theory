#include <iostream>
#include "func.h"

using namespace std;

void graph_trans::forward_adjacency()
{
    for (int i = 0; i < n; i++)
    {
        adjacency_node** pnode = &(adjacency_table[i]);
        for (int j = forward_table[0][i]; j < forward_table[0][i + 1]; j++)
        {
            *pnode = new adjacency_node;
            (*pnode)->terminal = forward_table[1][j];
            (*pnode)->weight = forward_table[2][j];
            (*pnode)->next = nullptr;
            pnode = &((*pnode)->next);
        }
    }
}