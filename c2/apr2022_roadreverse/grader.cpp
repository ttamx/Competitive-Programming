#include "roadreverse.cpp"
#include <iostream>

static int N_123456790, M_123456790, K_123456790;
static std::vector<std::vector<int>> S_123456790;
static std::vector<std::pair<int,int>> R_123456790;

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::cin >> N_123456790 >> M_123456790 >> K_123456790;

  int rc = 0;
  for(int i=0; i<K_123456790; i++) {
    int l,u;
    std::cin >> l;
    std::vector<int> rr;
    
    for(int i=0; i<l; i++) {
      std::cin >> u;
      rr.push_back(u);
    }
    S_123456790.push_back(rr);
    rc += l;
  }
  int mleft = M_123456790 - rc;
  for(int i=0; i<mleft; i++) {
    int u,v;
    std::cin >> u >> v;
    R_123456790.push_back(std::make_pair(u,v));
  }
  std::cout << count_roads(N_123456790,M_123456790,K_123456790,S_123456790,R_123456790) << std::endl;
}
