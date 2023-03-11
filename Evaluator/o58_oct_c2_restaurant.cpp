#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int N=305;

int n,t;
int a[N][N],p[N],deg[N];
vector<tuple<int,int,int>> v;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> t;
    iota(p,p+n+1,0);
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)cin >> a[i][j];
    for(int i=2;i<=n;++i)for(int j=1;j<i;++j)v.emplace_back(a[i][j],i,j);
    sort(v.begin(),v.end());
    for(auto [d,i,j]:v){
        if(fp(i)==fp(j))continue;
        p[p[i]]=p[j];
        ++deg[i],++deg[j];
    }
    for(int i=1;i<=n;++i){
        if(deg[i]>=3){
            cout << i << '\n';
            if(t==2)cout << deg[i];
            return 0;
        }
    }
}
