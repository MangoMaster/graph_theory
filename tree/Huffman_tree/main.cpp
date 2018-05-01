#include <iostream>
#include <fstream>
#include "huffman.h"

using namespace std;

int main()
{
    Huffman h("input.txt");
    int num = h.count();
    
    ofstream fout;
    fout.open("output.txt");
    fout << num << endl;
    fout.close();

    h.output("test.txt");

    return 0;
}