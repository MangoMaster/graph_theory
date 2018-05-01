#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <queue>
#include <stack>
#include <vector>
#include <iostream>

/**
 * @brief 带权值的键值
 * 
 * @tparam T 键值的类型
 */
template <typename T>
struct Node
{
  public:
    T key;      // 键值，0为虚拟结点
    int weight; // 权值

    Node(){};
    Node(const T &k, int w) : key(k), weight(w){};
    friend bool operator<(const Node &left, const Node &right)
    {
        return left.weight < right.weight;
    }
    friend std::ostream &operator<<(std::ostream &os, const Node &right)
    {
        os << '(' << right.key << ',' << right.weight << ')' << ' ';
        return os;
    }
};

template <typename T>
struct HuffmanNode
{
  public:
    Node<T> node;
    std::vector<int> num; // 标号，与键值对应，虚拟节点标号为子节点标号数列

    HuffmanNode(){};
    HuffmanNode(const Node<T> &d) : node(d){};
    HuffmanNode(const Node<T> &d, int n) : node(d)
    {
        num.push_back(n);
    }

    class node_cmp // 用于priority_queue
    {
      public:
        bool operator()(const HuffmanNode<T> &left, const HuffmanNode<T> &right)
        {
            return !(left.node < right.node);
        }
    };
};

template <typename T>
struct HuffmanCoding
{
    Node<T> node;
    std::stack<int> coding; // 编号

    HuffmanCoding(){};
    HuffmanCoding(const Node<T> &d) : node(d){};
};

class Huffman
{
  public:
    Huffman(){};
    Huffman(const std::string &input_file_name)
    {
        input(input_file_name);
    }
    ~Huffman(){};
    void input(const std::string &input_file_name);
    int count();                                      // 计数
    void solve();                                     // 给出具体实现
    void output(const std::string &output_file_name); // 输出具体实现

  private:
    std::vector<Node<char>> node_vector;
    std::priority_queue<HuffmanNode<char>, std::vector<HuffmanNode<char>>, HuffmanNode<char>::node_cmp> huffman_process;
    std::vector<HuffmanCoding<char>> huffman_coding;
    void lazy_init();
};

#endif // HUFFMAN_H_