#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e5+5;
const ll MOD=1e9+7;

int n,m,cnt;
int fa[2*N];
ll pw[N];
bool con;

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

void uni(int u,int v){
    u=fp(u),v=fp(v);
    if(u==v)return;
    fa[u]=v;
    cnt--;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    cnt=2*n;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=2*pw[i-1]%MOD;
    iota(fa,fa+2*n+1,0);
    while(m--){
        int t,u,v;
        cin >> t >> u >> v;
        if(t)uni(u,v),uni(u+n,v+n);
        else uni(u,v+n),uni(u+n,v);
        if(cnt&1)con=true;
        cout << (con?0:pw[cnt/2]) << "\n";
    }
}