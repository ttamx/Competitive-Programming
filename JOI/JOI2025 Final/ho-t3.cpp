#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;
const int Q=4e5+5;
const ll INF=1e10;

int n,m,p,q;
vector<pair<ll,ll>> range,norm_range;
ll ql[Q],qr[Q],qx[Q];
vector<int> queries;
bool bad[Q];
vector<int> adj[N];

struct SuffixMin{
    map<ll,ll> mp;
    ll query(ll i){
        auto it=mp.lower_bound(i);
        if(it==mp.end())return INF;
        return it->second;
    }
    void update(ll i,ll v){
        if(v>=query(i))return;
        mp[i]=v;
        auto it=mp.find(i);
        while(it!=mp.begin()&&(--it)->second>=v){
            it=mp.erase(it);
        }
    }
}min_left,min_size;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> p;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[b].emplace_back(c);
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> ql[i] >> qr[i] >> qx[i];
    }
    for(int i=2;i<=n;i++){
        if(adj[i].empty()){
            for(int i=0;i<q;i++){
                cout << "No\n";
            }
            exit(0);
        }
    }
    queries.resize(q);
    iota(queries.begin(),queries.end(),1);
    sort(queries.begin(),queries.end(),[&](int i,int j){
        return ql[i]<ql[j]||(ql[i]==ql[j]&&qr[i]<qr[j]);
    });
    for(int i=2;i<=n;i++){
        sort(adj[i].begin(),adj[i].end());
        ll pre=-INF;
        for(auto x:adj[i]){
            range.emplace_back(pre,x);
            pre=x;
        }
        range.emplace_back(pre,INF);
    }
    sort(range.begin(),range.end(),[&](pair<ll,ll> x,pair<ll,ll> y){
        return x.first<y.first||(x.first==y.first&&x.second>y.second);
    });
    for(auto [l,r]:range){
        if(norm_range.empty()||r>norm_range.back().second){
            norm_range.emplace_back(l,r);
        }
    }
    range=move(norm_range);
    int cur=0;
    ll mx=0;
    for(auto i:queries){
        while(cur<range.size()&&range[cur].first<ql[i]){
            auto [l,r]=range[cur];
            min_left.update(r,l);
            min_size.update(mx,mx-l);
            mx=r;
            cur++;
        }
        if(mx-qr[i]<=qx[i]){
            continue;
        }
        if(ql[i]-min_left.query(qr[i]+1)<=qx[i]){
            continue;
        }
        if(min_size.query(qr[i]+1)>qr[i]-ql[i]+qx[i]){
            bad[i]=true;
        }
    }
    for(int i=1;i<=q;i++){
        cout << (bad[i]?"No":"Yes") << "\n";
    }
}