#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const int N=250005;
const ll INF=LLONG_MAX/2;

int n,k;
int a[N];
vector<pair<int,int>> adj[N],radj[N];
ll dist[N];
int par[N],ptr[N];
int s,t;
vector<int> ch[N];
vector<ll> ans;

void link(int u,int v,int w){
    adj[u].emplace_back(v,w);
    radj[v].emplace_back(u,w);
}

struct Node{
    ll key;
    int val,rank,l,r;
};
vector<Node> nodes(1);

int new_node(ll key,int val,int rank,int l,int r){
    nodes.emplace_back(Node{key,val,rank,l,r});
    return nodes.size()-1;
}

int insert(int t,ll key,int val){
    if(!t||key<=nodes[t].key)return new_node(key,val,0,t,0);
    int l=nodes[t].l,r=insert(nodes[t].r,key,val);
    if(!l||nodes[r].rank>nodes[l].rank)swap(l,r);
    return new_node(nodes[t].key,nodes[t].val,r?nodes[r].rank+1:0,l,r);
}

void solve(){
    for(int i=1;i<=n+2;i++)dist[i]=INF;
    priority_queue<P,vector<P>,greater<P>> pq;
    pq.emplace(dist[t]=0,t);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:radj[u])if(d+w<dist[v]){
            pq.emplace(dist[v]=d+w,v);
            par[v]=u;
        }
    }
    if(dist[s]==INF)return;
    for(int i=1;i<=n+2;i++)if(par[i])ch[par[i]].emplace_back(i);
    queue<int> q;
    q.emplace(t);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        bool f=false;
        for(auto [v,w]:adj[u])if(dist[v]<INF){
            ll c=w+dist[v]-dist[u];
            if(!c&&!f&&v==par[u]){
                f=true;
                continue;
            }
            ptr[u]=insert(ptr[u],c,v);
        }
        for(auto v:ch[u]){
            ptr[v]=ptr[u];
            q.emplace(v);
        }
    }
    ans.emplace_back(dist[s]);
    if(!ptr[s])return;
    pq.emplace(dist[s]+nodes[ptr[s]].key,ptr[s]);
    while(!pq.empty()&&ans.size()<k){
        auto [d,u]=pq.top();
        pq.pop();
        ans.emplace_back(d);
        ll key=nodes[u].key;
        int v=nodes[u].val,l=nodes[u].l,r=nodes[u].r;
        if(ptr[v])pq.emplace(d+nodes[ptr[v]].key,ptr[v]);
        if(l)pq.emplace(d+nodes[l].key-key,l);
        if(r)pq.emplace(d+nodes[r].key-key,r);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    if(n==1){
        cout << a[1] << "\n";
        for(int i=1;i<k;i++)cout << "-1\n";
        exit(0);
    }
    s=n+1,t=n+2;
    link(s,1,a[1]),link(s,2,a[2]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=3&&i+j<=n;j++){
            link(i,i+j,a[i+j]);
        }
    }
    link(n-1,t,0),link(n,t,0);
    solve();
    ans.resize(k,-1);
    for(auto x:ans)cout << x << "\n";
}