#ifndef GRAPHBUILDER_H_
#define GRAPHBIULDER_H_

#include <vector>

class GraphBuilder
{
  public:
    GraphBuilder(const std::vector<std::vector<int>> &g, const std::vector<int> &c, const std::vector<int> &m)
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
    const std::vector<std::vector<int>> &getNetworkFlowGraph() const
    {
        return networkFlowGraph;
    }
    int getTotalNegativeCost() const
    {
        return totalNegativeCost;
    }

  private:
    const std::vector<std::vector<int>> &binaryGraph;
    const std::vector<int> &cost;
    std::vector<int> reversedMatches;
    std::vector<std::vector<int>> networkFlowGraph;
    int nNode;
    int totalNegativeCost;
    void reverseMatches(const std::vector<int> &matches);
};

#endif // GRAPHBUILDER_H_