#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e5+5;
const ll mod=1e9+7;

int n,m,cnt;
int fa[2*N];
ll pw[N];
bool con;

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

bool chk(int u,int v){
    return fp(u)==fp(v);
}

void uni(int u,int v){
    if(chk(u,v))return;
    cnt--;
    fa[fp(u)]=fp(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    cnt=2*n;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=2*pw[i-1]%mod;
    iota(fa,fa+2*n+1,0);
    while(m--){
        int t,u,v;
        cin >> t >> u >> v;
        if(t)uni(u,v),uni(u+n,v+n);
        else uni(u,v+n),uni(u+n,v);
        con|=chk(u,u+n)||chk(v,v+n);
        cout << (con?0:pw[cnt/2]) << '\n';
    }
}