#include<bits/stdc++.h>

using namespace std;

const bool DBG=false;
const int N=1e5+5;

int n,k;
vector<pair<int,int>> v;
set<pair<int,int>> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    v.resize(n);
    for(auto &[x,y]:v)cin >> x >> y;
    if(k==1)cout << 0,exit(0);
    sort(v.begin(),v.end(),[&](pair<int,int> a,pair<int,int> b){
        return a.second<b.second;
    });
    long long res=0;
    for(int i=0;i<k;i++)s.emplace(v[i]);
    for(auto it=next(s.begin());it!=s.end();it=next(it))res+=abs(it->second-prev(it)->second);
    long long ans=res+prev(s.end())->first-s.begin()->first;
    if(DBG){
        for(auto [x,y]:s)cerr << "(" << x << "," << y << ") ";
        cerr << "\n" << res+prev(s.end())->first-s.begin()->first << "\n";
    }
    for(int i=k;i<n;i++){
        auto it=s.lower_bound(v[i-k]);
        if(it!=s.begin())res-=abs(it->second-prev(it)->second);
        if(it!=prev(s.end()))res-=abs(it->second-next(it)->second);
        if(it!=s.begin()&&it!=prev(s.end()))res+=abs(prev(it)->second-next(it)->second);
        s.erase(it);
        it=s.emplace(v[i]).first;
        if(it!=s.begin()&&it!=prev(s.end()))res-=abs(prev(it)->second-next(it)->second);
        if(it!=s.begin())res+=abs(it->second-prev(it)->second);
        if(it!=prev(s.end()))res+=abs(it->second-next(it)->second);
        ans=min(ans,res+prev(s.end())->first-s.begin()->first);
        if(DBG){
            for(auto [x,y]:s)cerr << "(" << x << "," << y << ") ";
            cerr << "\n" << res+prev(s.end())->first-s.begin()->first << "\n";
        }
    }
    cout << ans;
}