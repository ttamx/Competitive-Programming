#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=5e5+5;
const int inf=2e9;

int n,q;
int v[N],a[N],b[N];
int lc[N],rc[N];
vector<p2> adj[N];
stack<int> s;
int sz[N],lv[N],cp[N],dist[20][N];
bool used[N];
int mx;
multiset<pair<p2,int>> ms[N];

int dfssz(int u,int p=0){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

void filldist(int u,int l,int d=0,int p=0){
    dist[l][u]=d;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])filldist(v,l,d+w,u);
}

void decom(int u,int p=0){
    u=centroid(u,dfssz(u));
    used[u]=true;
    cp[u]=p;
    lv[u]=lv[p]+1;
    filldist(u,lv[u]);
    for(auto [v,w]:adj[u])if(!used[v])decom(v,u);
}

void update(int st,int val){
    b[st]=val=min(b[st]+val,(int)1e9);
    mx=max(mx,val);
    for(int u=st,ch=-1;u!=0;ch=u,u=cp[u]){
        int d=dist[lv[u]][st]+a[st];
        auto it=ms[u].lower_bound({{val,0},-2});
        if(it!=ms[u].end()&&it->first.second<=d)continue;
        if(it!=ms[u].end()&&it->first.first==val)ms[u].erase(it);
        it=ms[u].insert({{val,d},ch});
        while(it!=ms[u].begin()&&it->first.second<=prev(it)->first.second)ms[u].erase(prev(it));
    }
}

int query(int st,int val){
    if(val>mx)return -1;
    int res=inf;
    for(int u=st,ch=-2;u!=0;ch=u,u=cp[u]){
        auto it=ms[u].lower_bound({{val,0},-2});
        if(it!=ms[u].end()&&it->second!=ch)res=min(res,dist[lv[u]][st]+it->first.second);
    }
    return (res+v[st])/2;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> v[i];
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]=max(0,v[i]-2*a[i]);
    }
    for(int i=1;i<=n;i++){
        while(!s.empty()&&v[s.top()]<v[i]){
            lc[i]=s.top();
            s.pop();
        }
        if(!s.empty())rc[s.top()]=i;
        s.emplace(i);
    }
    for(int i=1;i<=n;i++){
        if(lc[i]){
            int w=v[i]-v[lc[i]];
            adj[i].emplace_back(lc[i],w);
            adj[lc[i]].emplace_back(i,w);
        }
        if(rc[i]){
            int w=v[i]-v[rc[i]];
            adj[i].emplace_back(rc[i],w);
            adj[rc[i]].emplace_back(i,w);
        }
    }
    decom(1);
    while(q--){
        int t,x,y;
        cin >> t >> x >> y;
        if(t==1){
            update(x,y);
        }else{
            cout << query(x,y) << "\n";
        }
    }
}