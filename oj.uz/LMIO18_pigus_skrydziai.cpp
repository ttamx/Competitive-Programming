#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    vector<pair<int,int>> mx(n),mx2(n);
    map<pair<int,int>,int> mp;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        a[u]+=w,a[v]+=w;
        mp[minmax(u,v)]=w;
        mx2[u]=max(mx2[u],{w,v});
        if(mx[u]<mx2[u])swap(mx[u],mx2[u]);
        mx2[v]=max(mx2[v],{w,u});
        if(mx[v]<mx2[v])swap(mx[v],mx2[v]);
    }
    ll ans=*max_element(a.begin(),a.end());
    for(int i=0;i<n;i++){
        if(mx2[i].first){
            auto [w1,u]=mx[i];
            auto [w2,v]=mx2[i];
            auto it=mp.find(minmax(u,v));
            if(it!=mp.end())ans=max(ans,(ll)w1+w2+it->second);
        }
    }
    cout << ans;
}