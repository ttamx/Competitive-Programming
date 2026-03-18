#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

struct SuffixMin{
    map<ll,ll> dat;
    void insert(ll i,ll v){
        auto it=dat.lower_bound(i);
        if(it!=dat.end()&&it->second<=v)return;
        it=dat.insert(it,{i,v});
        it->second=v;
        while(it!=dat.begin()&&prev(it)->second>=v)dat.erase(prev(it));
    }
    ll query(ll i){
        auto it=dat.lower_bound(i);
        return it==dat.end()?INF:it->second;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    ll a,b;
    cin >> n >> q >> a >> b;
    vector<tuple<ll,ll,ll,int>> p;
    for(int i=0;i<n;i++){
        ll x,y,c;
        cin >> x >> y >> c;
        p.emplace_back(x,y,c,-1);
    }
    for(int i=0;i<q;i++){
        ll x,y;
        cin >> x >> y;
        p.emplace_back(x,y,0LL,i);
    }
    vector<ll> ans(q,INF);
    for(int t=0;t<4;t++){
        SuffixMin ds;
        sort(p.begin(),p.end());
        for(auto &[x,y,c,i]:p){
            if(i==-1){
                ds.insert(y,y*b-x*a+c);
            }else{
                ans[i]=min(ans[i],ds.query(y)+x*a-y*b);
            }
            tie(x,y)=make_pair(y,-x);
        }
        swap(a,b);
    }
    for(auto x:ans){
        cout << x << "\n";
    }
}