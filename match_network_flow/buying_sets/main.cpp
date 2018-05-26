#include <cstdlib>
#include <iostream>
#include <cassert>
#include "loader.h"
#include "matcher.h"
#include "graphbuilder.h"
#include "FlowMaxer.h"

using namespace std;

int main()
{
    freopen("input3.txt", "r", stdin);
    Loader l;
    l.load();

    Matcher m(l.getGraph());
    m.match();
    assert(m.getMatches().size() == l.getGraph().size()); // 保证是完全匹配

    GraphBuilder b(l.getGraph(), l.getCost(), m.getMatches());
    b.build();

    FlowMaxer f(b.getNetworkFlowGraph());
    f.compute();

    // 代价 = 所有负权点的权值之和 + 最大流流量
    cout <<  b.getTotalNegativeCost() + f.getMaxFlow() << endl;

    return 0;
}