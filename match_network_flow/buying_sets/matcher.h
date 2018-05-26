#ifndef MATCHER_H_
#define MATCHER_H_

#include <vector>

class Matcher
{
public:
  Matcher(const std::vector<std::vector<int>> &g) : graph(g)
  {
    nX = graph.size();
    matches.resize(nX, -1);
    searchX.reserve(nX);
    searchY.reserve(nX);
    companionY.reserve(nX);
  }
  void match();
  const std::vector<int> &getMatches() const
  {
    return matches;
  }

private:
  const std::vector<std::vector<int>> &graph;
  std::vector<int> matches;
  int nX;
  std::vector<int> searchX;
  std::vector<int> searchY;
  std::vector<int> companionY;
  int findExpandable();
  void expand();
  int findCompanionOfy(int y) const;
  int findMatchOfy(int y) const;
};

#endif // MATCHER_H_