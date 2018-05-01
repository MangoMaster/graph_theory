#include <iostream>
#include <fstream>
#include "dijkstra.h"

using namespace std;

void dijkstra::print()
{
    ofstream fout;
    fout.open("output.txt");

    if (!fout.is_open())
    {
        cout << "ERROR: outputfile is not open properly." << endl;
        return;
    }

    for (int i = 0 ; i < n; i++)
    {
        if (i == k) // 起始结点
        {
            continue;
        }
        else if (document[i].chosen == false) // 不连通
        {
            fout << -1 << " ";
        }
        else
        {
            fout << document[i].shortest_path << " ";
        }
    }

    fout.close();
}