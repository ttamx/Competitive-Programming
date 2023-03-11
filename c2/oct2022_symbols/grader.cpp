#include "symbols.h"
#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, q;
  std::cin >> n >> q;
  explore_site(n, q);
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    std::cout << retrieve_notes(l, r) << std::endl;
  }
  return 0;
}