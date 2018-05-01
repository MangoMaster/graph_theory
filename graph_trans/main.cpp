#include <iostream>
#include "func.h"

using namespace std;

int main()
{
    graph_trans g;
    g.weight_forward();
    g.forward_edge();
    g.edge_incidence();
    g.forward_adjacency();
    g.output();
    return 0;
}