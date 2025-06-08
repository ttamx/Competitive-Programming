#include<bits/stdc++.h>

using namespace std;

struct PrefixMax{
    map<int,int> dat;
    void update(int i,int v){
        i=-i;
        auto it=dat.lower_bound(i);
        if(it!=dat.end()&&v<=it->second)return;
        it=dat.insert(it,{i,v});
        it->second=v;
        while(it!=dat.begin()&&prev(it)->second<=v)dat.erase(prev(it));
    }
    int query(int i){
        auto it=dat.lower_bound(-i);
        return it==dat.end()?0:it->second;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m,k,n;
    cin >> m >> k >> n;
    map<int,vector<pair<int,int>>> mp;
    for(int i=0;i<n;i++){
        int p,w,t;
        cin >> p >> w >> t;
        mp[t].emplace_back(p,w);
    }
    PrefixMax all;
    vector<PrefixMax> ds(m);
    int ans=0;
    for(auto &[_,v]:mp){
        vector<tuple<int,int,int>> upd;
        for(auto [p,w]:v){
            int cur=max(all.query(p-1)-k,ds[w].query(p-1))+1;
            upd.emplace_back(p,w,cur);
            ans=max(ans,cur);
        }
        for(auto [p,w,val]:upd){
            ds[w].update(p,val);
            all.update(p,val);
        }
    }
    cout << ans << "\n";
}