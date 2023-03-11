#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,q,ans;
int h[N],p[N];
set<int> s;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;++i){
        cin >> h[i];
    }
    for(int i=0;i<m;++i){
        int u,v;
        cin >> u >> v;
        u=fp(u),v=fp(v);
        if(h[u]>h[v])swap(u,v);
        p[v]=p[u];
    }
    for(int i=1;i<=n;++i){
        int u=fp(i);
        s.insert(h[u]);
    }
    auto it=s.begin();
    ans=(*it)*s.size();
    it++;
    while(it!=s.end()){
        ans+=*it;
        it++;
    }
    for(auto it:s)cout << it << ' ';
    cout << ans;
}