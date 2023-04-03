#include <cstdio>
#include <cassert>
#include <cmath>
int goal[201][201];
int col[201][201];
int n;
int cmds = 0;

static inline bool bound(int val)
{
  return 1 <= val && val <= n;
}

int main(int argc, char *argv[])
{
  int i, j;
  assert(freopen(argv[3], "w", stdout));
  if (!freopen(argv[1], "r", stdin))
  {
    printf("Can't open input file.\n");
    return 0;
  }
  assert(scanf("%d", &n) == 1);
  for (i = 1; i <= n; i++)
  {
    for (j = 1; j <= n; j++)
    {
      assert(scanf("%d", &goal[i][j]) == 1);
      col[i][j] = 0;
    }
  }
  if (!freopen(argv[2], "r", stdin))
  {
    printf("Can't open output file.\n");
    return 0;
  }
  int r1, c1, r2, c2;
  int args = scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
  while (args == 4)
  {
    cmds++;
    if (cmds > 2 * n * n)
    {
      printf("Too many commands.\n");
      return 0;
    }
    if (!bound(r1) || !bound(c1) || !bound(r2) || !bound(c2))
    {
      printf("Number out of bounds.\n");
      return 0;
    }
    int stepi, stepj, steps;
    if (r1 == r2 && c1 <= c2)
    {
      stepi = 0;
      stepj = 1;
      steps = c2 - c1;
    }
    else if (c1 == c2 && r1 <= r2)
    {
      stepi = 1;
      stepj = 0;
      steps = r2 - r1;
    }
    else if (r2 - r1 == c2 - c1 && r2 - r1 >= 0)
    {
      stepi = 1;
      stepj = 1;
      steps = r2 - r1;
    }
    else if (r2 - r1 == c1 - c2 && r2 - r1 >= 0)
    {
      stepi = 1;
      stepj = -1;
      steps = r2 - r1;
    }
    else
    {
      printf("Command invalid.\n");
    }
    for (int i = 0; i <= steps; i++)
    {
      col[r1 + stepi * i][c1 + stepj * i]++;
      col[r1 + stepi * i][c1 + stepj * i] %= 3;
    }
    args = scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
  }
  if (args != 1 || r1 != -1)
  {
    printf("Formatting incorrect.\n");
  }
  for (i = 1; i <= n; i++)
  {
    for (j = 1; j <= n; j++)
    {
      if (col[i][j] != goal[i][j])
      {
        printf("Cell (%d, %d) has incorrect color.\n", i, j);
        return 0;
      }
    }
  }
  printf("CORRECT!\nScore: %d\n", cmds);
  return 0;
}
