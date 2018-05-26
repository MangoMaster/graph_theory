#include <iostream>
#include "loader.h"

using namespace std;

// 从文件载入图，形式：第一维为所有集合，第二维为每个集合中的元素序号(=元素-1)
void Loader::load()
{
    cin >> n;
    graph.resize(n);
    for (int i = 0; i < n; ++i)
    {
        int number;
        cin >> number;
        graph[i].reserve(number);
        for (int j = 0; j < number; ++j)
        {
            int num;
            cin >> num;
            // 所有集合中的元素均减一，从0开始
            graph[i].push_back(num - 1);
        }
    }

    cost.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        cost.push_back(num);
    }

    /*cout << "binary graph: " << endl;
    for (int i = 0; i < graph.size(); ++i)
    {
        for (int j = 0; j < graph[i].size(); ++j)
            cout << graph[i][j] << " ";
        cout << endl;
    }
    cout << endl;*/
}