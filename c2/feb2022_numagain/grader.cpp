#include <stdio.h>
#include <vector>
#include "numagain.h"
int main()
{
    int N;
    scanf("%d",&N);
    std::vector<int>number(N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&number[i]);
    }
    printf("%d\n",find_ans(number));
    return 0;
}
