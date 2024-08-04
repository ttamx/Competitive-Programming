#include "soccer.cpp"
#include <cassert>
#include <cstdio>
#include <vector>
 
int main()
{
    int N;
    assert(1 == scanf("%d", &N));
    std::vector<std::vector<int>> F(N, std::vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            assert(1 == scanf("%d", &F[i][j]));
        }
    }
    fclose(stdin);

    int res = biggest_stadium(N, F);

    printf("%d\n", res);
    fclose(stdout);
    return 0;
}
