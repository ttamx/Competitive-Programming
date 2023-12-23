#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

struct DSU{
    vector<int> p,sz;
    DSU(int n=0){
        init(n+1);
    }
    void init(int n){
        p.resize(n);
        iota(p.begin(),p.end(),0);
        sz.assign(n,1);
    }
    int fp(int u){
        return p[u]=(u==p[u]?u:fp(p[u]));
    }
    bool same(int u,int v){
        return fp(u)==fp(v);
    }
    bool merge(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        sz[u]+=sz[v];
        p[v]=u;
        return true;
    }
    int sz(int u){
        return sz[fp(u)];
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
}