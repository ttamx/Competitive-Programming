#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct CHT{
    struct Line{
        ll m,c;
        ll eval(ll x){return m*x+c;};
    };
    vector<Line> hull;
    bool bad(const Line &x,const Line &y,const Line &z){
        return __int128_t(x.c-z.c)*(y.m-x.m)<=__int128_t(x.c-y.c)*(z.m-x.m);
    }
    void insert(ll m,ll c){
        Line v{m,c};
        while(hull.size()>1&&bad(hull.end()[-2],hull.back(),v))hull.pop_back();
        hull.emplace_back(v);
    }
    ll query(ll x){
        int l=0,r=hull.size()-1;
        while(l<r){
            int m=(l+r)/2;
            if(hull[m].eval(x)<hull[m+1].eval(x))l=m+1;
            else r=m;
        }
        return hull[l].eval(x);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<ll> a(n),b(n),c(n),ans(q);
    for(int i=1;i<n;i++)cin >> a[i];
    for(auto &x:c)cin >> x;
    for(int i=1;i<n;i++)b[i]=b[i-1]+a[i]*c[i];
    for(int i=1;i<n;i++)a[i]+=a[i-1];
    vector<vector<pair<int,int>>> qr(n);
    for(int i=0;i<q;i++){
        int u,v;
        cin >> u >> v;
        if(u<v)qr[u].emplace_back(v,i);
        else ans[i]=b[u]-b[v];
    }
    CHT cht;
    for(int i=0;i<n;i++){
        cht.insert(c[i],b[i]+a[i]*c[i]);
        for(auto [v,j]:qr[i])ans[j]=b[i]-cht.query(-a[v]);
    }
    for(auto x:ans)cout << x << "\n";
}