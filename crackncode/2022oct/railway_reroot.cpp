#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=100'005;
const ll INF=LLONG_MAX/2;
const bool DBG=false;

int n;
int a[N];
vector<pair<int,int>> adj[N];
int par[N];
ll ans=INF;

struct Path{
    ll dp,cost,people;
}path[N];

struct Point{
    ll dp,cost,people;
    Point():dp(0LL),cost(0LL),people(0LL){} // default values for leaves
    friend ostream& operator<<(ostream &os,Point p){ // debuging trick
        os << "DP : " << p.dp << ", ";
        os << "COST : " << p.cost << ", ";
        os << "PEOPLE : " << p.people;
        return os;
    }
}point[N],up[N];

Point add_edge(Path p,int w){
    Point res;
    res.dp=p.dp-p.cost-p.people*w;
    res.cost=p.cost+p.people*w;
    res.people=p.people;
    return res;
}

Point rake(Point l,Point r){
    Point res;
    res.dp=min(l.dp,r.dp);
    res.cost=l.cost+r.cost;
    res.people=l.people+r.people;
    return res;
}

Path compress(Point p,int u){
    Path res;
    res.dp=p.dp+p.cost;
    res.cost=p.cost;
    res.people=p.people+a[u];
    return res;
}

void dfs(int u){
    for(auto [v,w]:adj[u]){
        if(v==par[u])continue;
        par[v]=u;
        dfs(v);
        point[u]=rake(point[u],add_edge(path[v],w));
    }
    path[u]=compress(point[u],u);
}

void reroot(int u){
    if(DBG){
        cerr << "NODE " << u << "\n";
        cerr << up[u] << "\n";
    }
    for(int t=0;t<2;t++){ // rake head and tail
        Point sum;
        for(auto [v,w]:adj[u]){
            if(v==par[u])continue;
            up[v]=rake(up[v],sum);
            sum=rake(sum,add_edge(path[v],w));
        }
        reverse(adj[u].begin(),adj[u].end());
    }
    for(auto [v,w]:adj[u]){
        if(v==par[u])continue;
        up[v]=rake(up[v],up[u]); // rake parent of u with head and tail
        up[v]=add_edge(compress(up[v],u),w); // pass value to node v
        reroot(v);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    par[0]=-1;
    dfs(0);
    reroot(0);
    for(int u=0;u<n;u++){ // find answer for each root
        Path p=compress(rake(point[u],up[u]),u); // rake subtree of u and parent of u
        ans=min(ans,p.dp);
        if(DBG){
            cerr << p.dp << " \n"[u==n-1];
        }
    }
    cout << ans;
}