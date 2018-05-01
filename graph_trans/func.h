#ifndef FUNC_H
#define FUNC_H

// weight matrix 权矩阵
// incidence matrix 关联矩阵
// edge list 边列表
// forward table 正向表
// adjacency table 邻接表
#include <vector>

class graph_trans
{
  public:
    void weight_incidence();
    void weight_edge();
    void weight_forward();
    void weight_adjacency();
    void edge_incidence();
    void forward_edge();
    void forward_adjacency();
    graph_trans();
    ~graph_trans();
    void output();

  private:
    int n;  // 结点数
    int m;  // 边数
    const char *inputfilename = "input.txt";
    const char *outputfilename = "output.txt";
    struct adjacency_node
    {
        int terminal;
        int weight;
        adjacency_node* next;
    };
    void load();
    std::vector<std::vector<int> > weight_matrix;
    std::vector<std::vector<int> > incidence_matrix;
    std::vector<std::vector<int> > edge_list;
    std::vector<std::vector<int> > forward_table;
    std::vector<adjacency_node*> adjacency_table;  
};

#endif // FUNC_H