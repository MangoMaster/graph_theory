#include <iostream>
#include "func.h"

using namespace std;

void graph_trans::weight_forward()
{
    int num = 0;    // 这里的num从0开始
    forward_table[0][0] = num;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (weight_matrix[i][j] != 0)
            {
                forward_table[1].push_back(j);
                forward_table[2].push_back(weight_matrix[i][j]);
                num++;
            }
        }
        forward_table[0][i + 1] = num;
    }
}