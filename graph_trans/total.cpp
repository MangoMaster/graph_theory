#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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
    int n; // 结点数
    int m; // 边数
    const char *inputfilename = "input.txt";
    const char *outputfilename = "output.txt";
    struct adjacency_node
    {
        int terminal;
        int weight;
        adjacency_node *next;
    };
    void load();
    std::vector<std::vector<int> > weight_matrix;
    std::vector<std::vector<int> > incidence_matrix;
    std::vector<std::vector<int> > edge_list;
    std::vector<std::vector<int> > forward_table;
    std::vector<adjacency_node *> adjacency_table;
};

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

graph_trans::graph_trans()
{
    n = 0;
    m = 0;

    load();

    incidence_matrix.resize(n);
    for (int i = 0; i < n; i++)
    {
        incidence_matrix[i].reserve(m);
    }

    edge_list.resize(3);
    for (int i = 0; i < 3; i++)
    {
        edge_list[i].reserve(m);
    }

    forward_table.resize(3);
    forward_table[0].resize(n + 1);
    for (int i = 1; i < 3; i++)
    {
        forward_table[i].reserve(m);
    }

    adjacency_table.resize(n, NULL);
}

graph_trans::~graph_trans()
{
    for (int i = 0; i < n; i++)
    {
        adjacency_node *p = adjacency_table[i];
        if (p == NULL)
            continue;
        adjacency_node *q = p->next;
        delete p;
        while (q != NULL)
        {
            p = q;
            q = p->next;
            delete p;
        }
    }
}

void graph_trans::weight_incidence()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (weight_matrix[i][j] != 0)
            {
                incidence_matrix[i].push_back(1);
                incidence_matrix[j].push_back(-1);
                for (int k = 0; k < n; k++)
                    if (k != i && k != j)
                        incidence_matrix[k].push_back(0);
            }
        }
    }
}

void graph_trans::weight_edge()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (weight_matrix[i][j] != 0)
            {
                edge_list[0].push_back(i);
                edge_list[1].push_back(j);
                edge_list[2].push_back(weight_matrix[i][j]);
            }
        }
    }
}

void graph_trans::weight_forward()
{
    int num = 0; // 这里的num从0开始
    forward_table[0][0] = num;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (weight_matrix[i][j] != 0)
            {
                forward_table[1].push_back(j);
                forward_table[2].push_back(weight_matrix[i][j]);
                num++;
            }
        }
        forward_table[0][i + 1] = num;
    }
}

void graph_trans::weight_adjacency()
{
    for (int i = 0; i < n; i++)
    {
        adjacency_node **pnode = &adjacency_table[i];
        for (int j = 0; j < n; j++)
        {
            if (weight_matrix[i][j] != 0)
            {
                *pnode = new adjacency_node;
                (*pnode)->terminal = j;
                (*pnode)->weight = weight_matrix[i][j];
                (*pnode)->next = NULL;
                pnode = &((*pnode)->next);
            }
        }
    }
}

void graph_trans::edge_incidence()
{
    for (int i = 0; i < m; i++)
    {
        incidence_matrix[edge_list[0][i]].push_back(1);
        incidence_matrix[edge_list[1][i]].push_back(-1);
        for (int j = 0; j < n; j++)
        {
            if (j != edge_list[0][i] && j != edge_list[1][i])
                incidence_matrix[j].push_back(0);
        }
    }
}

void graph_trans::forward_edge()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = forward_table[0][i]; j < forward_table[0][i + 1]; j++)
        {
            edge_list[0].push_back(i);
            edge_list[1].push_back(forward_table[1][j]);
            edge_list[2].push_back(forward_table[2][j]);
        }
    }
}

void graph_trans::forward_adjacency()
{
    for (int i = 0; i < n; i++)
    {
        adjacency_node **pnode = &(adjacency_table[i]);
        for (int j = forward_table[0][i]; j < forward_table[0][i + 1]; j++)
        {
            *pnode = new adjacency_node;
            (*pnode)->terminal = forward_table[1][j];
            (*pnode)->weight = forward_table[2][j];
            (*pnode)->next = NULL;
            pnode = &((*pnode)->next);
        }
    }
}

void graph_trans::output()
{
    ofstream fout;
    fout.open(outputfilename);

    if (!fout.is_open())
    {
        cout << "error: output file is not open properly." << endl;
        return;
    }

    const int STARTDIFF = 1; // 从0开始和从1开始的区别

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
        while (temp != NULL)
        {
            fout << temp->weight << " " << temp->terminal + STARTDIFF << " ";
            temp = temp->next;
        }
        fout << endl;
    }

    fout.close();
}

int main()
{
    graph_trans g;
    g.weight_forward();
    g.forward_edge();
    g.edge_incidence();
    g.forward_adjacency();
    g.output();
    return 0;
}