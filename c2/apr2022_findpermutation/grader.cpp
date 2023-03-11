#include "inversion.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

static int n;
static std::vector<int> arr, tmp;
static int cnt;

static inline long long get_inversion() {
  long long inversion = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr.at(i) > arr.at(j)) {
        inversion++;
      }
    }
  }
  return inversion;
}

long long swap_and_report(int i, int j) {
  cnt++;
  assert(i >= 0 && i < n);
  assert(j >= 0 && j < n);
  std::swap(arr.at(i), arr.at(j));
  return get_inversion();
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  assert(std::cin >> n);
  std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(arr));
  tmp = arr;
  std::sort(tmp.begin(), tmp.end());
  assert(std::unique(tmp.begin(), tmp.end()) == tmp.end() and
         *std::max_element(tmp.begin(), tmp.end()) == n and
         *std::min_element(tmp.begin(), tmp.end()) == 1);
  tmp = arr;
  if (find_permutation(n, get_inversion()) == tmp) {
    std::cout << cnt << std::endl;
  } else {
    std::cout << "Wrong Answer" << std::endl;
  }
}