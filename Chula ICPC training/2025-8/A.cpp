#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
int a[N],fa[N];

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        fa[i]=i;
    }
    while(m--){
        int u,v;
        cin >> u >> v;
        u=fp(u),v=fp(v);
        a[u]=min(a[u],a[v]);
        fa[v]=u;
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(fp(i)==i){
            ans+=a[i];
        }
    }
    cout << ans << "\n";
}