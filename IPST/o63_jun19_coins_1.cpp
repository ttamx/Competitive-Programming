#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,mx;
int a[i],qs[N],dp[N][N];
vector<int> pos[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;++i){cin >> a[i];pos[a[i]].emplace_back(i);mx=max(mx,a[i])}
    for(int i=1;i<=n;++i){cin >> qs[i];qs[i]+=qs[i-1]}
    int pre=-1,now=0;
    for(auto i:v){

    }
}
