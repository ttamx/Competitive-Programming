#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2005;
const int NN=N*N;

int n;
ll a[N];
int match[N];
vector<int> adj[NN];
bool vis[NN];
vector<int> path;

inline bool kuhn(int u){
    if(vis[u])return false;
    vis[u]=true;
    path.emplace_back(u);
    for(auto v:adj[u])if(!match[v]||kuhn(match[v])){
        match[v]=u;
        return true;
    }
    return false;
}

void solve(){
    cin >> n;
    vector<pair<ll,int>> vec;
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pq.emplace(a[i],i);
    }
    int buf=1,cnt=0;
    while(true){
        ++buf;
        auto [val,u]=pq.top();
        pq.pop();
        adj[buf]={u};
        while(!pq.empty()&&pq.top().first==val){
            adj[buf].emplace_back(pq.top().second);
            pq.pop();
        }
        if(kuhn(buf)){
            for(auto u:path)vis[u]=false;
            vector<int>().swap(path);
            cnt++;
            if(cnt==n){
                cout << val << "\n";
                break;
            }
            for(auto v:adj[buf]){
                pq.emplace(val+a[v],v);
            }
        }
    }
    for(int i=1;i<=n;i++)match[i]=0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}