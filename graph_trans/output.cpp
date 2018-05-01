#include <iostream>
#include <fstream>
#include "func.h"

using namespace std;

void graph_trans::output()
{
    ofstream fout;
    fout.open(outputfilename);

    if (!fout.is_open())
    {
        cout << "error: output file is not open properly." << endl;
        return;
    }

    const int STARTDIFF = 1;    // 从0开始和从1开始的区别

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fout << incidence_matrix[i][j] << " ";
        }
        fout << endl;
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fout << edge_list[i][j] + STARTDIFF << " ";
        }
        fout << endl;
    }
    for (int j = 0; j < m; j++)
        fout << edge_list[2][j] << " ";
    fout << endl;

    for (int j = 0; j < n + 1; j++)
        fout << forward_table[0][j] + STARTDIFF << " ";
    fout << endl;
    for (int j = 0; j < m; j++)
        fout << forward_table[1][j] + STARTDIFF << " ";
    fout << endl;
    for (int j = 0; j < m; j++)
        fout << forward_table[2][j] << " ";
    fout << endl;

    for (int i = 0; i < n; i++)
    {
        adjacency_node *temp = adjacency_table[i];
        while (temp != nullptr)
        {
            fout << temp->weight << " " << temp->terminal + STARTDIFF << " ";
            temp = temp->next;
        }
        fout << endl;
    }

    fout.close();
}