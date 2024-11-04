#include "marbletracks.cpp"
#include <cstdio>
#include <vector>
#include <utility>
#include <tuple>

using std::vector;
using std::tuple;
using std::get;

int main() {
    int N, Q;
    int tmp;
    tmp = scanf("%d %d",&N,&Q);
    vector<int> v(N);
    vector<tuple<int, int, int>>queries(Q);
    for(int i = 0;i < N;i++) {
        tmp = scanf("%d",&v[i]);
    }
    for(int i = 0;i < Q;i++) {
        tmp = scanf("%d %d %d", &get<0>(queries[i]), &get<1>(queries[i]), &get<2>(queries[i]));
    }
    vector<int> vs = observe(N,Q,v,queries);
    for(auto i: vs) {
        printf("%d\n",i);
    }
}