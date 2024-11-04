#include<bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    vector<int> l(m),r(m);
    vector<int> cnt(n+2);
    for(int i=0;i<m;i++){
        cin >> l[i] >> r[i];
        cnt[l[i]]++;
        cnt[r[i]+1]--;
    }
    vector<pair<ll,int>> qrs;
    vector<ll> ans(q);
    for(int i=0;i<q;i++){
        ll s;
        cin >> s;
        qrs.emplace_back(s,i);
    }
    sort(qrs.rbegin(),qrs.rend());
    vector<pair<ll,int>> a;
    map<int,pair<int,ll>> mp;
    mp[1]={n,-1e18};
    ll t=0;
    ll base=0;
    for(int i=1;i<=n;i++){
        cnt[i]+=cnt[i-1];
        base+=max(0,cnt[i]-1);
    }
    for(int i=0;i<m;i++){
        auto it=prev(mp.upper_bound(l[i]));
        if(it->first<l[i]){
            mp[l[i]]=it->second;
            mp[l[i]].second+=l[i]-it->first;
            it->second.first=l[i]-1;
            it++;
        }
        for(;it!=mp.end()&&it->first<=r[i];it=mp.erase(it)){
            int cl=it->first;
            int cr=min(r[i],it->second.first);
            ll pt=it->second.second;
            int sz=cr-cl+1;
            a.emplace_back(t+cl-l[i]-pt,sz);
            if(cr<it->second.first){
                mp[cr+1]=it->second;
                mp[cr+1].second+=sz;
            }
        }
        mp[l[i]]={r[i],t};
        t+=r[i]-l[i]+1;
    }
    a.emplace_back(1e18,0);
    sort(a.begin(),a.end());
    for(auto [x,y]:a){
        while(!qrs.empty()&&qrs.back().first<x){
            ans[qrs.back().second]=base;
            qrs.pop_back();
        }
        base-=y;
    }
    for(auto x:ans){
        cout << x << " ";
    }
}