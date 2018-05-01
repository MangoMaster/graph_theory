#include <iostream>
#include "func.h"

using namespace std;

graph_trans::~graph_trans()
{
    for (int i = 0; i < n; i++)
    {
        adjacency_node *p = adjacency_table[i];
        if (p == nullptr)
            continue;
        adjacency_node *q = p->next;
        delete p;
        while (q != nullptr)
        {
            p = q;
            q = p->next;
            delete p;
        }
    }
}