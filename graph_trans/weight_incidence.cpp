#include <iostream>
#include "func.h"

using namespace std;

void graph_trans::weight_incidence()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (weight_matrix[i][j] != 0)
            {
                incidence_matrix[i].push_back(1);
                incidence_matrix[j].push_back(-1);
                for (int k = 0; k < n; k++)
                    if (k != i && k != j)
                        incidence_matrix[k].push_back(0);
            }
        }
    }
}