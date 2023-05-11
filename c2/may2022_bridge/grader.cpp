#include "bridge.cpp"
#include <iostream>

int main()
{
  int N;
  std::vector<int> W;

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
    
  std::cin >> N;

  for(int i=0; i<N; i++) {
    int w;
    std::cin >> w;
    W.push_back(w);
  }

  long long answer = destroy_bridge(N, W);

  std::cout << answer << std::endl;
}
