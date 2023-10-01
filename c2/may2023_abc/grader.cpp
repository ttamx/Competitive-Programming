#include "abc.cpp"
#include <string>
#include <iostream>
#include <utility>

int main()
{
  std::string S;
  std::cin >> S;
  std::pair<int,int> ans = max_unbalance(S);
  std::cout << ans.first << " " << ans.second << std::endl;
}
