#include "longest.cpp"
#include <stdio.h>
#include <vector>
#include <cassert>

std::vector<std::pair<int,int>> adj[5010];
std::vector<long long> Answer;
long long mmax=0,dis[5050][5050];
int cnt;

long long f(int a, int b) {return dis[std::min(a,b)][std::max(a,b)];}

bool find(int a, int b, int x) {
    ++cnt;
    return f(a,x)<f(b,x);
}

void dfs(int x, int par, int start, long long D) {
    mmax=std::max(D,mmax);
    for (auto s : adj[x]) {
        if (s.first==par) continue;
        if (s.first>start) continue;
        dis[s.first][start]=D+s.second;
        dfs(s.first,x,start,dis[s.first][start]);
    }
}

int main() {
    int N;
    assert(scanf("%d",&N));

    for (int i=1; i<N; ++i) {
        int a,w;
        assert(scanf("%d%d",&a,&w)==2);
        adj[i].push_back(std::pair<int,int>(a,w));
        adj[a].push_back(std::pair<int,int>(i,w));
    }

    for (int i=0; i<N; ++i) {
        dfs(i,i,i,0);
        Answer.push_back(mmax);
    }

    std::vector<std::pair<int,int>> result=longest(N);

    if (result.size()!=N) {
        printf("the returned vector has wrong size");
        return 0;
    }

    for (int i=0; i<N; ++i) {
        if (result[i].first>i) {
            printf("the city %d haven't been built in year %d",result[i].first,i);
            return 0;
        }
        if (result[i].second>i) {
            printf("the city %d haven't been built in year %d",result[i].second,i);
            return 0;
        }

        if (result[i].first<0 || result[i].second<0) {
            printf("city less than 0");
            return 0;
        }
    }

    for (int i=0; i<N; ++i) {
        if (f(result[i].first,result[i].second)!=Answer[i]) {
            printf("%d and %d is not a diameter of the graph consisting node 0 to %d",result[i].first,result[i].second,i);
            return 0;
        }
    }

    printf("function used : %d",cnt);
}