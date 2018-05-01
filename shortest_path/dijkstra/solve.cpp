#include <iostream>
#include "dijkstra.h"

using namespace std;

void dijkstra::solve()
{
    // 初始化
    document.resize(n, {false, MAX_LENGTH});
    document[k].chosen = true;
    document[k].shortest_path = 0;
    // 正向表方法
    for (int i = forward_table[0][k]; i < forward_table[0][k + 1]; i++)
    {
        document[forward_table[1][i]].shortest_path = forward_table[2][i];
    }
    
    // 权矩阵方法
    /*for (int i = 0; i < n; i++)
    {
        if (weight_matrix[k][i] != 0)
        {
            document[i].shortest_path = weight_matrix[k][i];
        }
    }*/

    // 输出最短路径
    /*for (int i = 0; i < n; i++)
    {
        cout << document[i].shortest_path << " ";
    }
    cout << endl;*/

    for (int i = 0; i < n - 1; i++) // 最多n-1次迭代
    {
        int minid = -1;
        int minlength = MAX_LENGTH;

        // 寻找最短的最短路径
        // 搜索方法
        for (int j = 0; j < n; j++)
        {
            if (document[j].chosen == false 
               && document[j].shortest_path < minlength)
            {
                minid = j;
                minlength = document[j].shortest_path;
            }
        }

        // 输出minid和minlength
        //cout << minid << " " << minlength << endl;

        if (minid == -1) // 图不连通
        {
            break;
        }
        else // 将该节点放入S中
        {
            document[minid].chosen = true;
        }

        // 更新最短路径
        // 正向表方法
        for (int j = forward_table[0][minid]; j < forward_table[0][minid + 1]; j++)
        {
            if (document[forward_table[1][j]].chosen == false)
            {
                int temp = forward_table[2][j] + minlength;
                if (temp < document[forward_table[1][j]].shortest_path)
                {
                    document[forward_table[1][j]].shortest_path = temp;
                }
            }
        }

        // 权矩阵方法
        /*for (int j = 0; j < n; j++)
        {
            if (document[j].chosen == false
                && weight_matrix[minid][j] != 0)
            {
                int temp = minlength + weight_matrix[minid][j];
                if (temp < document[j].shortest_path)
                {
                    document[j].shortest_path = temp;
                }
            }
        }*/

        // 输出最短路径
        /*for (int i = 0; i < n; i++)
        {
            cout << document[i].shortest_path << " ";
        }
        cout << endl;*/
    }
}