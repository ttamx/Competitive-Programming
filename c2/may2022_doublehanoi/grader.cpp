#include "hanoi.cpp"
#include <vector>
#include <iostream>

static int N;
static std::vector<int> S0,S1,S2;
static std::vector<int> T0,T1,T2;

int main()
{
  std::cin >> N;
  int l,d;

  std::cin >> l;
  for(int i=0; i<l; i++) {
    std::cin >> d;
    S0.push_back(d);
  }
  std::cin >> l;
  for(int i=0; i<l; i++) {
    std::cin >> d;
    S1.push_back(d);
  }
  std::cin >> l;
  for(int i=0; i<l; i++) {
    std::cin >> d;
    S2.push_back(d);
  }

  std::cin >> l;
  for(int i=0; i<l; i++) {
    std::cin >> d;
    T0.push_back(d);
  }
  std::cin >> l;
  for(int i=0; i<l; i++) {
    std::cin >> d;
    T1.push_back(d);
  }
  std::cin >> l;
  for(int i=0; i<l; i++) {
    std::cin >> d;
    T2.push_back(d);
  }

  long long answer = hanoi(N, S0,S1,S2, T0,T1,T2);

  std::cout << answer << std::endl;
}
