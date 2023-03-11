#include "2eggs.cpp"
#include <iostream>

static int N, H, Q;
static int drop_count;
static bool active1, active2;

void fail(std::string s) {
  std::cerr << s << std::endl;
  exit(1);
}

bool drop_egg(int egg_number, int h) {
  cout << "drop " << egg_number << " at " << h << '\n';
  if (h < 1 || h > N)
    fail("invalid height");
  if (egg_number < 1 || egg_number > 2)
    fail("invalid egg number");
  if (egg_number == 1) {
    if (!active1)
      fail("egg 1 is already broken");
  } else if (egg_number == 2) {
    if (!active2)
      fail("egg 2 is already broken");
  }
  drop_count++;
  if (h > H) {
    if (egg_number == 1)
      active1 = false;
    else if (egg_number == 2)
      active2 = false;
    return true;
  } else {
    return false;
  }
}

int main() {
  std::cin >> N >> H >> Q;
  drop_count = 0;
  active1 = active2 = true;
  int hp1 = height_threshold(N, Q);
  std::cout << hp1 << std::endl;
  std::cout << drop_count << std::endl;
  return 0;
}