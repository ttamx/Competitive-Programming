#include "manager.cpp"
#include <iostream>

int main()
{
  int N, Q;
  std::vector<int> A;
  
  std::cin >> N >> Q;
  for(int i=0; i<N; i++) {
    int a;
    std::cin >> a;
    A.push_back(a);
  }

  initialize(N, Q, A);

  for(int i=0; i<Q; i++) {
    int l, r, x;
    std::cin >> l >> r >> x;

    std::cout << min_managers(l, r , x) << std::endl;
  }
}
