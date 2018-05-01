#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


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

dijkstra::dijkstra()
{
    load_forward_table();
}


dijkstra::~dijkstra()
{
}

void dijkstra::load_forward_table()
{
    ifstream fin;
    fin.open("input.txt");

    if (!fin.is_open())
    {
        cout << "ERROR: inputfile is not open properly." << endl;
        return;
    }

    fin >> n;

    // 初始化正向表
    forward_table.resize(3);
    for (int i = 0; i < 3; i++)
        forward_table[i].reserve(n + 1); // 可能浪费空间，加快速度
    int m = 0;                           // 计算边数
    forward_table[0].push_back(m);

    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        for (int j = 0; j < n; j++)
        {
            fin >> temp;
            if (temp != 0)
            {
                m++;
                forward_table[1].push_back(j);
                forward_table[2].push_back(temp);
            }
        }
        forward_table[0].push_back(m);
    }

    fin >> k;
    k--; // 从0开始编号

    fin.close();
}

void dijkstra::print()
{
    ofstream fout;
    fout.open("output.txt");

    if (!fout.is_open())
    {
        cout << "ERROR: outputfile is not open properly." << endl;
        return;
    }

    for (int i = 0 ; i < n; i++)
    {
        if (i == k) // 起始结点
        {
            continue;
        }
        else if (document[i].chosen == false) // 不连通
        {
            fout << -1 << " ";
        }
        else
        {
            fout << document[i].shortest_path << " ";
        }
    }

    fout.close();
}

void dijkstra::solve()
{
    // 初始化
    document.resize(n);
    for (int i = 0; i < n; i++)
    {
        document[i].chosen = false;
        document[i].shortest_path = MAX_LENGTH;
    }
    document[k].chosen = true;
    document[k].shortest_path = 0;
    // 正向表方法
    for (int i = forward_table[0][k]; i < forward_table[0][k + 1]; i++)
    {
        document[forward_table[1][i]].shortest_path = forward_table[2][i];
    }
    
    // 权矩阵方法
    /*for (int i = 0; i < n; i++)
    {
        if (weight_matrix[k][i] != 0)
        {
            document[i].shortest_path = weight_matrix[k][i];
        }
    }*/

    // 输出最短路径
    /*for (int i = 0; i < n; i++)
    {
        cout << document[i].shortest_path << " ";
    }
    cout << endl;*/

    for (int i = 0; i < n - 1; i++) // 最多n-1次迭代
    {
        int minid = -1;
        int minlength = MAX_LENGTH;

        // 寻找最短的最短路径
        for (int j = 0; j < n; j++)
        {
            if (document[j].chosen == false 
               && document[j].shortest_path < minlength)
            {
                minid = j;
                minlength = document[j].shortest_path;
            }
        }

        // 输出minid和minlength
        //cout << minid << " " << minlength << endl;

        if (minid == -1) // 图不连通
        {
            break;
        }
        else // 将该节点放入S中
        {
            document[minid].chosen = true;
        }

        // 更新最短路径
        // 正向表方法
        for (int j = forward_table[0][minid]; j < forward_table[0][minid + 1]; j++)
        {
            if (document[forward_table[1][j]].chosen == false)
            {
                int temp = forward_table[2][j] + minlength;
                if (temp < document[forward_table[1][j]].shortest_path)
                {
                    document[forward_table[1][j]].shortest_path = temp;
                }
            }
        }

        // 权矩阵方法
        /*for (int j = 0; j < n; j++)
        {
            if (document[j].chosen == false
                && weight_matrix[minid][j] != 0)
            {
                int temp = minlength + weight_matrix[minid][j];
                if (temp < document[j].shortest_path)
                {
                    document[j].shortest_path = temp;
                }
            }
        }*/

        // 输出最短路径
        /*for (int i = 0; i < n; i++)
        {
            cout << document[i].shortest_path << " ";
        }
        cout << endl;*/
    }
}

int main()
{
    dijkstra d;
    d.solve();
    d.print();
    return 0;
}