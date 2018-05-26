#include <iostream>
#include <iomanip>
#include "graphbuilder.h"

using namespace std;

void GraphBuilder::reverseMatches(const std::vector<int> &matches)
{
    reversedMatches.resize(matches.size());
    for (int i = 0; i < matches.size(); ++i)
        reversedMatches[matches[i]] = i;
}

void GraphBuilder::build()
{
    // 其余点与源结点、汇结点相连
    for (int i = 0; i < cost.size(); ++i)
        if (cost[i] < 0)
        {
            // 负权点与源结点(nNode - 2)相连，边权为点权相反数
            networkFlowGraph[nNode - 2][i] = -cost[i];
            totalNegativeCost += cost[i];
        }
        else
        {
            // 正权点与汇结点(nNode - 1)相连，边权为点权
            networkFlowGraph[i][nNode - 1] = cost[i];
        }

    // 其余点彼此相连，边权为无穷
    for (int i = 0; i < binaryGraph.size(); ++i)
        for (int j = 0; j < binaryGraph[i].size(); ++j)
        {
            int k = reversedMatches[binaryGraph[i][j]];
            networkFlowGraph[i][k] = INT_MAX;
        }

    /*cout << "network flow graph: " << endl;
    for (int i = 0; i < networkFlowGraph.size(); ++i)
    {
        for (int j = 0; j < networkFlowGraph[i].size(); ++j)
            cout << setw(10) << networkFlowGraph[i][j] << "  ";
        cout << endl;
    }
    cout << endl;*/
}