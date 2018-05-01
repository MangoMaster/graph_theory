#include <iostream>
#include <fstream>
#include "func.h"

using namespace std;

void graph_trans::load()
{
    ifstream fin;
    fin.open(inputfilename);

    if (!fin.is_open())
    {
        cout << "error: input file is not properly open." << endl;
        return;
    }

    fin >> n;

    weight_matrix.resize(n);
    for (int i = 0; i < n; i++)
    {
        weight_matrix[i].reserve(n);
    }

    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> temp;
            weight_matrix[i].push_back(temp);
            if (temp != 0)
                m++;
        }
    }

    fin.close();
}