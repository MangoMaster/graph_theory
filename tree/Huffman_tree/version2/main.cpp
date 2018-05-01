#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "huffman.h"

using namespace std;

int main()
{
    const string INPUT_FILE = "input.txt";
    const string OUTPUT_FILE = "output.txt";

    ifstream fin;
    fin.open(INPUT_FILE);
    if (!fin.is_open())
        throw runtime_error(INPUT_FILE + " is not open properly");
    multiset<char> my_multiset;
    while (!fin.eof())
    {
        char buffer[256];
        fin.read(buffer, 256);
        int number = fin.gcount();
        for (int i = 0; i < number; ++i)
            my_multiset.insert(buffer[i]);
    }
    fin.close();

    Huffman<char> h(my_multiset);
    int num = h.count();

    ofstream fout;
    fout.open(OUTPUT_FILE);
    fout << num << endl;
    fout.close();

    return 0;
}