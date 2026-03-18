#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n),adj2(n);
    for(int i=0;i<m;i++){
        int u,v,w,t;
        cin >> u >> v >> w >> t;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
        if(t==2){
            adj2[u].emplace_back(v,w);
            adj2[v].emplace_back(u,w);
        }
    }
    vector<ll> d1(n,INF),d2(n,INF);
    for(int t=0,s=0;t<2;t++,s=n-1){
        priority_queue<P,vector<P>,greater<P>> pq;
        pq.emplace(d1[s]=0,s);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(d>d1[u])continue;
            for(auto [v,w]:adj[u]){
                if(d+w<d1[v]){
                    pq.emplace(d1[v]=d+w,v);
                }
            }
        }
        swap(d1,d2);
        swap(adj,adj2);
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){return d1[i]<d1[j];});
    int q;
    cin >> q;
    vector<pair<int,int>> qr;
    for(int i=0;i<q;i++){
        int x;
        cin >> x;
        qr.emplace_back(x,i);
    }
    sort(qr.begin(),qr.end());
    vector<ll> ans(q);
    ll base=INF;
    int p=0;
    for(auto [x,i]:qr){
        while(p<n&&d1[ord[p]]<=x){
            base=min(base,d1[ord[p]]+d2[ord[p]]);
            p++;
        }
        ans[i]=(base<INF?base:-1LL);
    }
    for(auto x:ans){
        cout << x << "\n";
    }
}