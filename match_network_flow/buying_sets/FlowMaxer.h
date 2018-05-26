#ifndef FLOWMAXER_H_
#define FLOWMAXER_H_

#include <vector>
#include <queue>

struct networkFlowLabel
{
    int direction; //+-1
    int lastNodeNumber;
    int flow;
};

class FlowMaxer
{
  public:
    FlowMaxer(const std::vector<std::vector<int>> &g) : networkFlowGraph(g)
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
    const std::vector<std::vector<int>> &networkFlowGraph;
    int n;
    std::vector<std::vector<int>> currentFlow;
    std::vector<networkFlowLabel> currentLabel;
    std::queue<int> labeledNodeNumber;
    int maxFlow;
    int label();
    void boost();
    void initLabel();
};

#endif // FLOWMAXER_H_