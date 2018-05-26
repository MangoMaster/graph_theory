#include <iostream>
#include <algorithm>
#include <cassert>
#include "FlowMaxer.h"

using namespace std;

void FlowMaxer::compute()
{
    while (true)
    {
        initLabel();
        int labelable = 0;
        while (labelable == 0)
            labelable = label();

        /*cout << "current label: " << endl;
        for (int i = 0; i < currentLabel.size(); ++i)
        {
            cout << "number " << i
                 << " direction " << currentLabel[i].direction
                 << " lastNodeNumber " << currentLabel[i].lastNodeNumber
                 << " flow " << currentLabel[i].flow << endl;
        }
        cout << endl;*/

        if (labelable == 1)
            boost();
        else if (labelable == -1)
            break;
    }

    /*cout << "max flow: " << endl;
    for (int i = 0; i < currentFlow.size(); ++i)
    {
        for (int j = 0; j < currentFlow[i].size(); ++j)
            cout << currentFlow[i][j] << "  ";
        cout << endl;
    }
    cout << endl;*/
}

// 标号，无法标号返回-1，需要继续标号返回0，可增流返回1
int FlowMaxer::label()
{
    if (labeledNodeNumber.empty())
        return -1;
    int nodeNumber = labeledNodeNumber.front();
    labeledNodeNumber.pop();
    // 标号过程
    for (int i = 0; i < n; ++i)
        if (currentLabel[i].direction == 0 && networkFlowGraph[nodeNumber][i] > currentFlow[nodeNumber][i])
        {
            // i 为 nodeNumber 的后继结点，未标号，可增流
            labeledNodeNumber.push(i);
            currentLabel[i].direction = 1;
            currentLabel[i].lastNodeNumber = nodeNumber;
            currentLabel[i].flow = min(currentLabel[nodeNumber].flow, networkFlowGraph[nodeNumber][i] - currentFlow[nodeNumber][i]);
        }
    for (int i = 0; i < n; ++i)
        if (networkFlowGraph[i][nodeNumber] > 0 && currentLabel[i].direction == 0 && currentFlow[i][nodeNumber] > 0)
        {
            // i 为 nodeNumber 的前驱结点，未标号，可增流
            labeledNodeNumber.push(i);
            currentLabel[i].direction = -1;
            currentLabel[i].lastNodeNumber = nodeNumber;
            currentLabel[i].flow = min(currentLabel[nodeNumber].flow, currentFlow[i][nodeNumber]);
        }

    if (currentLabel[n - 1].direction != 0)
        return 1;
    else
        return 0;
}

// 初始化currentLabel labeledNodeNumber
void FlowMaxer::initLabel()
{
    networkFlowLabel label = {0, -1, 0};
    currentLabel.assign(n, label);
    currentLabel[n - 2].flow = INT_MAX;

    while (!labeledNodeNumber.empty())
        labeledNodeNumber.pop();
    labeledNodeNumber.push(n - 2);
}

// 增流
void FlowMaxer::boost()
{
    int boostFlow = currentLabel[n - 1].flow;
    int nodeNumber = n - 1;
    while (nodeNumber != n - 2)
    {
        networkFlowLabel label = currentLabel[nodeNumber];
        if (label.direction > 0)
            currentFlow[label.lastNodeNumber][nodeNumber] += boostFlow;
        else if (label.direction < 0)
            currentFlow[nodeNumber][label.lastNodeNumber] -= boostFlow;
        else
            assert(false);
        nodeNumber = label.lastNodeNumber;
    }
    maxFlow += boostFlow;

    /*cout << "current flow: " << endl;
    for (int i = 0; i < currentFlow.size(); ++i)
    {
        for (int j = 0; j < currentFlow[i].size(); ++j)
            cout << currentFlow[i][j] << "  ";
        cout << endl;
    }
    cout << endl;*/
}