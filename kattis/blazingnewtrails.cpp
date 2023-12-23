#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const int M=5e5+5;
const int lim=1e5+5;

int n,m,k,c;
bool spc[N];
bool imp;
vector<tuple<ll,int,int,int>> edge;

struct dsu_t{
    int p[N];
    void init(){
        iota(p+1,p+n+1,1);
    }
    int fp(int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    }
    bool uni(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        return p[v]=u,true;
    }
}dsu;

pair<ll,int> calc(ll lambda){
    int left=n-1,cnt=0;
    ll res=0;
    dsu.init();
    for(auto &[w,s,u,v]:edge)w-=lambda*s;
    sort(edge.begin(),edge.end());
    for(auto [w,s,u,v]:edge)if(dsu.uni(u,v)){
        res+=w;
        cnt-=s;
        left--;
    }
    if(left)imp=true;
    for(auto &[w,s,u,v]:edge)w+=lambda*s;
    return pair<ll,int>(res,cnt);
};

int cdiv(int a,int b){
    return a/b+((a^b)>0&&a%b);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k >> c;
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        spc[x]=true;
    }
    edge.resize(m);
    for(auto &[w,s,u,v]:edge)cin >> u >> v >> w,s=-(spc[u]^spc[v]);
    int l=-lim,r=lim;
    while(l<r){
        int m=cdiv(l+r,2);
        if(calc(m).second>=c)l=m;
        else r=m-1;
    }
    cout << ((l==-lim||imp)?-1:calc(l).first-1ll*l*c) << "\n";
}