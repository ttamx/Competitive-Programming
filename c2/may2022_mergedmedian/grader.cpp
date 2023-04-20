#include "mergedmedian.cpp"
#include <algorithm>

static std::vector<long long> a, b;
static int nnn;
static int cnt;

void fail(std::string s) {
  std::cerr << s << std::endl;
  exit(1);
}

long long alice(int i) {
  if (i < 0 || i > nnn){
    cerr << "alice " << i << "\n";
    fail("index out of bound");
  }
  cnt++;
  if (cnt > 300000)
    fail("too many questions");
  return a[i];
}
long long bob(int i) {
  if (i < 0 || i >= nnn){
    cerr << "bob " << i << "\n";
    fail("index out of bound");
  }
  cnt++;
  if (cnt > 300000)
    fail("too many questions");
  return b[i];
}

int main() {
  std::cin >> nnn;
  cnt = 0;
  for (int i = 0; i <= nnn; i++) {
    long long x;
    std::cin >> x;
    a.push_back(x);
  }
  for (int i = 0; i < nnn; i++) {
    long long x;
    std::cin >> x;
    b.push_back(x);
  }
  long long mm = find_merged_median(nnn);
  std::cout << mm << std::endl << cnt << std::endl;
  return 0;
}