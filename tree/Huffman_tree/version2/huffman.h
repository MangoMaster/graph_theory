#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <cassert>

template <typename T>
struct Node
{
    std::vector<int> num; // 序号，虚拟节点的序号为其子节点的序号数列
    T key;                // 键值，虚拟节点为0
    int weight;           // 权值

    Node(){};
    Node(const std::vector<T> &k, int w) : key(k), weight(w){};
    Node(int n, const std::vector<T> &k, int w) : key(k), weight(w)
    {
        num.push_back(n);
    }

    // 用于priority_queue，使priority_queue中weight最小的node在最前
    friend bool operator<(const Node &left, const Node &right)
    {
        return !(left.weight < right.weight);
    }
    friend std::ostream &operator<<(std::ostream &os, const Node &right)
    {
        os << "(" << right.key << "," << right.weight << ") ";
        return os;
    }
};

template <typename T>
struct Coding
{
    Node<T> node;
    std::stack<int> coding_vector;

    Coding(){};
    Coding(Node<T> n) : node(n){};
};

template <typename T>
class Huffman
{
  public:
    Huffman(const std::multiset<T> &s) : input_multiset(s){};
    ~Huffman(){};
    void solve();
    int count();
    void print();
    void print(const std::string &output_file);

  private:
    const std::multiset<T> &input_multiset;
    std::priority_queue<Node<T>> huffman_process;
    std::vector<Coding<T>> huffman_coding;
};

/************************functions**************************/

template <typename T>
void Huffman<T>::solve()
{
    using namespace std;

    if (input_multiset.empty())
        return;

    // lazy initialization
    int count_num = 0;
    for (auto it = input_multiset.begin(); it != input_multiset.end(); ++count_num)
    {
        Node<T> my_node(count_num, *it, input_multiset.count(*it));
        huffman_process.push(my_node);
        Coding<T> my_coding(my_node);
        huffman_coding.push_back(my_coding);
        for (int i = 0; i < my_node.weight; ++i)
            ++it;
    }

    int size = huffman_process.size();
    if (size == 1)
    {
        assert(huffman_coding.size() == 1);
        huffman_coding[0].coding_vector.push_back(0);
        return;
    }
    for (int i = 0; i < size - 1; ++i)
    {
        Node<T> node1 = huffman_process.top(); // left-child
        huffman_process.pop();
        Node<T> node2 = huffman_process.top(); // right-child
        huffman_process.pop();

        Node<T> new_node(0, node1.weight + node2.weight); // father
        for (auto it = node1.num.begin(); it != node2.num.end(); ++it)
        {
            new_node.num.push_back(*it);
            huffman_coding[*it].coding_vector.push_back(0);
        }
        for (auto it = node2.num.begin(); it != node2.num.end(); ++it)
        {
            new_node.num.push_back(*it);
            huffman_coding[*it].coding_vector.push_back(1);
        }
        huffman_process.push(new_node);
    }
    assert(huffman_process.size() == 1);
}

template <typename T>
int Huffman<T>::count()
{
    if (huffman_coding.empty())
        Huffman<T>::solve();
    
    int total = 0;
    for (auto it = huffman_coding.begin(); it != huffman_coding.end(); ++it)
        total += it->coding_vector.size() * it->node.weight;
    return total;
}

template <typename T>
void Huffman<T>::print()
{

}

template <typename T>
void Huffman<T>::print(const string& input_file)
{
    
}

#endif // HUFFMAN_H_