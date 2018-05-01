#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include "Huffman.h"

using namespace std;

void Huffman::input(const string &input_file_name)
{
    ifstream fin;
    fin.open(input_file_name.c_str());

    if (!fin.is_open())
        throw runtime_error(input_file_name + " is not open properly.");

    // lazy initialization
    const int CHARA_NUM = 26;
    node_vector.resize(CHARA_NUM);
    for (int i = 0; i < CHARA_NUM; ++i)
    {
        Node<char> temp;
        temp.key = static_cast<char>('a' + i);
        temp.weight = 0;
        node_vector[i] = temp;
    }

    while (!fin.eof())
    {
        char buffer[256];
        fin.read(buffer, 256);
        int read_num = fin.gcount();
        for (int i = 0; i < read_num; ++i)
            ++node_vector[buffer[i] - 'a'].weight;
    }

    fin.close();
}

void Huffman::solve()
{
    if (node_vector.empty()) // 空
        return;
    if (!huffman_coding.empty()) // 已经solve过了
        return;

    lazy_init();

    int size = huffman_process.size();
    if (size == 1)
    {
        assert(huffman_coding.size() == 1);
        huffman_coding[0].coding.push(0);
    }
    for (int i = 0; i < size - 1; ++i)
    {
        HuffmanNode<char> node1 = huffman_process.top();
        huffman_process.pop();
        HuffmanNode<char> node2 = huffman_process.top();
        huffman_process.pop();

        Node<char> new_node(0, node1.node.weight + node2.node.weight);
        HuffmanNode<char> new_huffman_node(new_node);
        for (auto it = node1.num.begin(); it != node1.num.end(); ++it)
        {
            new_huffman_node.num.push_back(*it);
            huffman_coding[*it].coding.push(0);
        }
        for (auto it = node2.num.begin(); it != node2.num.end(); ++it)
        {
            new_huffman_node.num.push_back(*it);
            huffman_coding[*it].coding.push(1);
        }
        huffman_process.push(new_huffman_node);

        // 检测正确性
        // cout << node1 << node2 << new_node << endl;
    }
    assert(huffman_process.size() == 1);
}

int Huffman::count()
{
    solve();

    int total = 0;
    for (auto it = huffman_coding.begin(); it != huffman_coding.end(); ++it)
        total += it->coding.size() * it->node.weight;

    return total;
}

void Huffman::output(const string &output_file_name)
{
    ofstream fout;
    fout.open(output_file_name.c_str());

    for (auto it = huffman_coding.begin(); it != huffman_coding.end(); ++it)
    {
        fout << it->node << '\t';
        while (!it->coding.empty())
        {
            fout << it->coding.top();
            it->coding.pop();
        }
        fout << endl;
    }

    fout.close();
}

void Huffman::lazy_init()
{
    // lazy initialization
    while (!huffman_process.empty())
        huffman_process.pop();
    int count = 0;
    for (auto it = node_vector.begin(); it != node_vector.end(); ++it)
        if (it->weight != 0)
        {
            HuffmanNode<char> temp1(*it, count);
            huffman_process.push(temp1);
            HuffmanCoding<char> temp2(*it);
            huffman_coding.push_back(temp2);
            ++count;
        }
}