#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>

class dijkstra
{
public:
  dijkstra();
  ~dijkstra();
  void solve();
  void print();

private:
  struct node
  {
    bool chosen;
    int shortest_path;
  };
  int n; // 结点数
  int k; // 起始结点编号
  static const int MAX_LENGTH = 10000;
  std::vector< std::vector<int> > forward_table;
  std::vector<node> document;
  void load_forward_table();
  dijkstra(dijkstra &);
};

#endif // DIJKSTRA_H