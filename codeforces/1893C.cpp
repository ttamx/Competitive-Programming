#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int m;
    cin >> m;
    vector<int> n(m);
    vector<ll> l(m),r(m),tot(m);
    vector<vector<ll>> c(m),a(m);
    map<ll,vector<pair<ll,int>>> mp;
    ll tl=0,tr=0;
    for(int i=0;i<m;i++){
        cin >> n[i] >> l[i] >> r[i];
        tl+=l[i];
        tr+=r[i];
        a[i].resize(n[i]);
        c[i].resize(n[i]);
        for(auto &x:a[i])cin >> x;
        for(int j=0;j<n[i];j++){
            cin >> c[i][j];
            tot[i]+=c[i][j];
            mp[a[i][j]].emplace_back(c[i][j],i);
        }
    }
    ll ans=tl;
    for(ll i=tl;i<=tr;i++){
        if(mp[i].empty())return void(cout << "0\n");
        ll d=i-tl;
        ll td=tr-tl;
        ll res=0;
        for(auto [bad,id]:mp[i]){
            td-=r[id]-l[id];
            ll good=tot[id]-bad;
            if(good>=l[id]){
                d-=min(good,r[id])-l[id];
                d=max(0ll,d);
            }else{
                res+=l[id]-good;
            }
        }
        d-=td;
        d=max(0ll,d);
        res+=d;
        ans=min(ans,res);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}