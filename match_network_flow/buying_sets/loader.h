#ifndef LOADER_H_
#define LOADER_H_

#include <string>
#include <vector>

class Loader
{
  public:
    void load();
    const std::vector<std::vector<int>> &getGraph()
    {
        return graph;
    }
    const std::vector<int> &getCost()
    {
        return cost;
    }

  private:
    int n;
    std::vector<std::vector<int>> graph;
    std::vector<int> cost;
};

#endif // LOADER_H_