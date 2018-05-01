#include "dijkstra.h"
#include <fstream>
#include <iostream>

using namespace std;

void dijkstra::load_forward_table()
{
    ifstream fin;
    fin.open("input.txt");

    if (!fin.is_open())
    {
        cout << "ERROR: inputfile is not open properly." << endl;
        return;
    }

    fin >> n;

    // 初始化正向表
    forward_table.resize(3);
    for (int i = 0; i < 3; i++)
        forward_table[i].reserve(n + 1); // 可能浪费空间，加快速度
    int m = 0;                           // 计算边数
    forward_table[0].push_back(m);

    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        for (int j = 0; j < n; j++)
        {
            fin >> temp;
            if (temp != 0)
            {
                m++;
                forward_table[1].push_back(j);
                forward_table[2].push_back(temp);
            }
        }
        forward_table[0].push_back(m);
    }

    fin >> k;
    k--; // 从0开始编号

    fin.close();
}