#include <iostream>
#include <cassert>
#include "matcher.h"

using namespace std;

void Matcher::match()
{
    // 逐个搜索
    for (int i = 0; i < nX; ++i)
    {
        searchX.clear();
        searchY.clear();
        companionY.clear();
        searchX.push_back(i);
        int expandable = 0;
        while (expandable == 0)
            expandable = findExpandable();

        /*cout << "searchX: ";
        for (int i = 0; i < searchX.size(); ++i)
            cout << searchX[i] << "  ";
        cout << endl;
        cout << "searchY: ";
        for (int j = 0; j < searchY.size(); ++j)
            cout << searchY[j] << "  ";
        cout << endl;
        cout << "companionY: ";
        for (int k = 0; k < companionY.size(); ++k)
            cout << companionY[k] << "  ";
        cout << endl;*/

        if (expandable == 1)
            expand();
    }

    /*cout << "matches: " << endl;
    for (int i = 0; i < matches.size(); ++i)
        cout << i << "    " << matches[i] << endl;
    cout << endl;*/
}

// 计算是否可增广，无法增广返回-1，需要继续计算返回0，可增广返回1
int Matcher::findExpandable()
{
    for (int i = 0; i < searchX.size(); ++i)
        for (int j = 0; j < graph[searchX[i]].size(); ++j)
        {
            // graph[searchX[i]][j] 属于 searchX的后继结点集合
            int y = graph[searchX[i]][j];
            if (findCompanionOfy(y) < 0)
            {
                // y 属于 (searchX的后继结点集合 - searchY)
                int x = findMatchOfy(y);
                int companion = searchX[i];
                if (x >= 0)
                {
                    // y 已匹配，需要继续计算
                    searchY.push_back(y);
                    companionY.push_back(companion);
                    searchX.push_back(x);
                    return 0;
                }
                else
                {
                    // y 尚未匹配，可增广
                    searchY.push_back(y);
                    companionY.push_back(companion);
                    return 1;
                }
            }
        }
    // searchX 的后继结点集合 == searchY，无法增广
    return -1;
}

// 寻找y在searchY中的位置，并返回companionY中对应位置的x值，没有返回-1
int Matcher::findCompanionOfy(int y) const
{
    for (int i = 0; i < searchY.size(); ++i)
        if (y == searchY[i])
            return companionY[i];
    return -1;
}

// 寻找y的匹配，没有返回-1
int Matcher::findMatchOfy(int y) const
{
    for (int i = 0; i < matches.size(); ++i)
        if (matches[i] == y)
            return i;
    return -1;
}

// 增广
void Matcher::expand()
{
    assert(searchX.size() == searchY.size());
    int y = searchY.back();
    int x = findCompanionOfy(y);
    while (true)
    {
        int nextY = matches[x]; // 保留x的原匹配
        matches[x] = y;

        if (nextY == -1) // 增广完成
            break;

        // 进行下一步增广
        y = nextY;
        x = findCompanionOfy(y);
    }

    /*cout << "matches: " << endl;
    for (int i = 0; i < matches.size(); ++i)
        cout << i << "    " << matches[i] << endl;
    cout << endl;*/
}