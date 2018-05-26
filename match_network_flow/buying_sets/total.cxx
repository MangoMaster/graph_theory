#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Loader
{
  public:
    void load();
    const std::vector<std::vector<int> > &getGraph()
    {
        return graph;
    }
    const std::vector<int> &getCost()
    {
        return cost;
    }

  private:
    int n;
    std::vector<std::vector<int> > graph;
    std::vector<int> cost;
};

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

class Matcher
{
public:
  Matcher(const std::vector<std::vector<int> > &g) : graph(g)
  {
    nX = graph.size();
    matches.resize(nX, -1);
    searchX.reserve(nX);
    searchY.reserve(nX);
    companionY.reserve(nX);
  }
  void match();
  const std::vector<int> &getMatches() const
  {
    return matches;
  }

private:
  const std::vector<std::vector<int> > &graph;
  std::vector<int> matches;
  int nX;
  std::vector<int> searchX;
  std::vector<int> searchY;
  std::vector<int> companionY;
  int findExpandable();
  void expand();
  int findCompanionOfy(int y) const;
  int findMatchOfy(int y) const;
};

void Matcher::match()
{
    // 逐个搜索
    for (int i = 0; i < nX; ++i)
    {
        searchX.clear();
        searchY.clear();
        companionY.clear();
        searchX.push_back(i);
        int expandable = 0;
        while (expandable == 0)
            expandable = findExpandable();

        /*cout << "searchX: ";
        for (int i = 0; i < searchX.size(); ++i)
            cout << searchX[i] << "  ";
        cout << endl;
        cout << "searchY: ";
        for (int j = 0; j < searchY.size(); ++j)
            cout << searchY[j] << "  ";
        cout << endl;
        cout << "companionY: ";
        for (int k = 0; k < companionY.size(); ++k)
            cout << companionY[k] << "  ";
        cout << endl;*/

        if (expandable == 1)
            expand();
    }

    /*cout << "matches: " << endl;
    for (int i = 0; i < matches.size(); ++i)
        cout << i << "    " << matches[i] << endl;
    cout << endl;*/
}

// 计算是否可增广，无法增广返回-1，需要继续计算返回0，可增广返回1
int Matcher::findExpandable()
{
    for (int i = 0; i < searchX.size(); ++i)
        for (int j = 0; j < graph[searchX[i]].size(); ++j)
        {
            // graph[searchX[i]][j] 属于 searchX的后继结点集合
            int y = graph[searchX[i]][j];
            if (findCompanionOfy(y) < 0)
            {
                // y 属于 (searchX的后继结点集合 - searchY)
                int x = findMatchOfy(y);
                int companion = searchX[i];
                if (x >= 0)
                {
                    // y 已匹配，需要继续计算
                    searchY.push_back(y);
                    companionY.push_back(companion);
                    searchX.push_back(x);
                    return 0;
                }
                else
                {
                    // y 尚未匹配，可增广
                    searchY.push_back(y);
                    companionY.push_back(companion);
                    return 1;
                }
            }
        }
    // searchX 的后继结点集合 == searchY，无法增广
    return -1;
}

// 寻找y在searchY中的位置，并返回companionY中对应位置的x值，没有返回-1
int Matcher::findCompanionOfy(int y) const
{
    for (int i = 0; i < searchY.size(); ++i)
        if (y == searchY[i])
            return companionY[i];
    return -1;
}

// 寻找y的匹配，没有返回-1
int Matcher::findMatchOfy(int y) const
{
    for (int i = 0; i < matches.size(); ++i)
        if (matches[i] == y)
            return i;
    return -1;
}

// 增广
void Matcher::expand()
{
    assert(searchX.size() == searchY.size());
    int y = searchY.back();
    int x = findCompanionOfy(y);
    while (true)
    {
        int nextY = matches[x]; // 保留x的原匹配
        matches[x] = y;

        if (nextY == -1) // 增广完成
            break;

        // 进行下一步增广
        y = nextY;
        x = findCompanionOfy(y);
    }

    /*cout << "matches: " << endl;
    for (int i = 0; i < matches.size(); ++i)
        cout << i << "    " << matches[i] << endl;
    cout << endl;*/
}
class GraphBuilder
{
  public:
    GraphBuilder(const std::vector<std::vector<int> > &g, const std::vector<int> &c, const std::vector<int> &m)
        : binaryGraph(g), cost(c)
    {
        reverseMatches(m);
        nNode = g.size() + 2; // 增加源结点(nNode - 2)、汇结点(nNode - 1)，其余节点编号不变
        networkFlowGraph.resize(nNode);
        for (int i = 0; i < nNode; ++i)
            networkFlowGraph[i].resize(nNode, 0);
        totalNegativeCost = 0;
    }
    void build();
    const std::vector<std::vector<int> > &getNetworkFlowGraph() const
    {
        return networkFlowGraph;
    }
    int getTotalNegativeCost() const
    {
        return totalNegativeCost;
    }

  private:
    const std::vector<std::vector<int> > &binaryGraph;
    const std::vector<int> &cost;
    std::vector<int> reversedMatches;
    std::vector<std::vector<int> > networkFlowGraph;
    int nNode;
    int totalNegativeCost;
    void reverseMatches(const std::vector<int> &matches);
};

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

struct networkFlowLabel
{
    int direction; //+-1
    int lastNodeNumber;
    int flow;
};

class FlowMaxer
{
  public:
    FlowMaxer(const std::vector<std::vector<int> > &g) : networkFlowGraph(g)
    {
        n = g.size();
        currentFlow.resize(n);
        for (int i = 0; i < n; ++i)
            currentFlow[i].resize(n, 0);
        maxFlow = 0;
    }
    void compute();
    int getMaxFlow() const
    {
        return maxFlow;
    }

  private:
    const std::vector<std::vector<int> > &networkFlowGraph;
    int n;
    std::vector<std::vector<int> > currentFlow;
    std::vector<networkFlowLabel> currentLabel;
    std::queue<int> labeledNodeNumber;
    int maxFlow;
    int label();
    void boost();
    void initLabel();
};

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
        else
            currentFlow[nodeNumber][label.lastNodeNumber] -= boostFlow;
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

int main()
{
    Loader l;
    l.load();

    Matcher m(l.getGraph());
    m.match();
    assert(m.getMatches().size() == l.getGraph().size()); // 保证是完全匹配

    GraphBuilder b(l.getGraph(), l.getCost(), m.getMatches());
    b.build();

    FlowMaxer f(b.getNetworkFlowGraph());
    f.compute();

    // 代价 = 所有负权点的权值之和 + 最大流流量
    cout << b.getTotalNegativeCost() + f.getMaxFlow() << endl;

    return 0;
}