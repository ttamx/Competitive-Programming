#include <cstdio>
#include <cmath>
#include <cassert>
int used[1000001];
int x[1000001], y[1000001], n, k, basket;
double dist = 0.0;
int main(int argc, char *argv[])
{
  int z, lastp = 0;
  assert(freopen(argv[3], "w", stdout));
  if (!freopen(argv[1], "r", stdin))
  {
    printf("Can't open input file.\n");
    return 0;
  }
  assert(scanf("%d", &n) == 1);
  assert(scanf("%d", &k) == 1);
  for (int i = 1; i <= n; i++)
  {
    assert(scanf("%d%d", &x[i], &y[i]) == 2);
  }
  if (!freopen(argv[2], "r", stdin))
  {
    printf("Can't open output file.\n");
    return 0;
  }
  basket = 0;
  assert(scanf("%d", &z) == 1);
  while (z != -1)
  {
    if (z == 0)
    {
      basket = 0;
      dist += sqrt(((double)(x[lastp] - x[z])) * ((double)(x[lastp] - x[z])) + ((double)(y[lastp] - y[z])) * ((double)(y[lastp] - y[z])));
      lastp = 0;
    }
    else if (z > 0 && z <= n)
    {
      if (basket >= k)
      {
        printf("Basket overloaded.\n");
        return 0;
      }
      else if (used[z])
      {
        printf("Ball %d picked twice.\n", z);
        return 0;
      }
      else
      {
        basket++;
        used[z]++;
        dist += sqrt(((double)(x[lastp] - x[z])) * ((double)(x[lastp] - x[z])) + ((double)(y[lastp] - y[z])) * ((double)(y[lastp] - y[z])));
        lastp = z;
      }
    }
    else
    {
      printf("Number out of bounds.\n");
      return 0;
    }
    assert(scanf("%d", &z) == 1);
  }
  if (lastp != 0)
  {
    printf("Did not end at 0.\n");
    return 0;
  }
  for (int i = 1; i <= n; i++)
  {
    if (!used[i])
    {
      printf("Ball %d never picked.\n", i);
      return 0;
    }
  }
  printf("CORRECT!\nScore: %.2lf\n", dist);
  return 0;
}
