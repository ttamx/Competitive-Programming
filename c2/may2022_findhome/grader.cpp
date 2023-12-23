#include "findhome.cpp"
#include <vector>
#include <iostream>
#include <cstdlib>

static const int MAX_N = 310;

static int C[MAX_N];
static int NN, Q;
static int check_count = 0;

int check(int u)
{
  check_count++;
  if(check_count > Q) {
    std::cout << "Too many calls to check" << std::endl;
    exit(0);
  }
  if((u < 0) || (u >= NN)) {
    std::cout << "Error calling check at " << u << std::endl;
    exit(0);
  }
  return C[u];
}

int main()
{
  std::vector<std::pair<int,int>> R;
  int M, H;

  std::cin >> NN >> M >> Q >> H;
  for(int i=0; i<M; i++) {
    int u,v;
    std::cin >> u >> v;
    R.push_back(std::make_pair(u,v));
  }
  for(int i=0; i<NN; i++) {
    int c;
    std::cin >> c;
    C[i] = c;
  }

  check_count = 0;
  int answer = find_home(NN, M, R);
  if(answer == H) {
    std::cout << "Correct\n";
  } else {
    std::cout << "Incorrect (answer = " << answer << ", correct answer = " << H << ")\n";
  }
  std::cout << check_count << " call(s) to check\n";
}
