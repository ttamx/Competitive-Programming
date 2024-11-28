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
    ll t=0;
    for(int i=0;i<m;i++){
        auto it=mp.lower_bound(l[i]);
        if(it!=mp.end()){
            int &pl=it->second.first;
            int pr=it->first;
            ll pt=it->second.second;
            if(pl<l[i]){
                mp[l[i]-1]={pl,pt-pr+l[i]-1};
                pl=l[i];
            }
        }
        for(;it!=mp.end()&&it->first<=r[i];it=mp.erase(it)){
            int cl=it->second.first;
            int cr=it->first;
            ll pt=it->second.second;
            a.emplace_back(t+cr-l[i]-pt,cr-cl+1);
        }
        if(it!=mp.end()){
            int &pl=it->second.first;
            int pr=it->first;
            ll pt=it->second.second;
            if(pl<=r[i]){
                a.emplace_back(t+pr-l[i]-pt,r[i]-pl+1);
                pl=r[i]+1;
            }
        }
        t+=r[i]-l[i]+1;
        mp[r[i]]={l[i],t};
    }
    a.emplace_back(-1,0);
    sort(a.begin(),a.end());
    ll base=0;
    for(auto [s,i]:qrs){
        while(a.back().first>=s){
            base+=a.back().second;
            a.pop_back();
        }
        ans[i]=base;
    }
    for(auto x:ans){
        cout << x << " ";
    }
}