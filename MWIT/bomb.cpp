#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(n);
    vector<tuple<int,int,int>> e;
    for(auto &[x,y]:a)cin >> x >> y;
    auto calc=[&](int i,int j){
        return (a[i].first-a[j].first)*(a[i].first-a[j].first)+(a[i].second-a[j].second)*(a[i].second-a[j].second);
    };
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)e.emplace_back(calc(i,j),i,j);
    sort(e.begin(),e.end());
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        if(u==p[u])return p[u];
        return p[u]=fp(p[u]);
    };
    int cnt=n,ans=0;
    for(auto [w,u,v]:e){
        if(cnt<=m)break;
        u=fp(u),v=fp(v);
        if(u==v)continue;
        cnt--;
        p[u]=v;
        ans=w;
    }
    cout << fixed << setprecision(3) << sqrt(ans);
}