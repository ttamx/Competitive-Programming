#include<bits/stdc++.h>

using namespace std;

const int N=205;
const int M=10005;

int n,m;
int u[M],v[M],t[M],c[M];
tuple<int,int,int> best(1e9,0,0);
vector<pair<int,int>> ans;

pair<int,int> mst(int mx,int my,bool save=false){
    auto calc=[&](int i){
        return mx*t[i]+my*c[i];
    };
    vector<int> ord(m);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return calc(i)<calc(j);
    });
    vector<int> fa(n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    int val=0,x=0,y=0;
    for(auto i:ord){
        int pu=fp(u[i]),pv=fp(v[i]);
        if(pu==pv)continue;
        if(save)ans.emplace_back(u[i],v[i]);
        val+=calc(i);
        x+=t[i],y+=c[i];
        fa[pv]=pu;
    }
    best=min(best,{x*y,mx,my});
    return {x,y};
}

void dnc(int xl,int yl,int xr,int yr){
    auto [xm,ym]=mst(yl-yr,xr-xl);
    if((xl-xr)*(ym-yr)-(xm-xr)*(yl-yr)<=0)return;
    dnc(xl,yl,xm,ym);
    dnc(xm,ym,xr,yr);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> u[i] >> v[i] >> t[i] >> c[i];
    }
    auto [xl,yl]=mst(1,0);
    auto [xr,yr]=mst(0,1);
    dnc(xl,yl,xr,yr);
    auto [res,mx,my]=best;
    auto [ansx,ansy]=mst(mx,my,true);
    cout << ansx << " " << ansy << "\n";
    for(auto [u,v]:ans){
        cout << u << " " << v << "\n";
    }
}