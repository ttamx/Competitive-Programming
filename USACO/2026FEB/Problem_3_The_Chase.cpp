#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int LG=19;
const int INF=1e9;

int n,m;
int a[N],deg[N],wait[N],pos[N];
vector<int> adj[N];
bool has[N],vis[N];
int ans[N];
vector<pair<int,int>> qr[N];
int mx[LG][N],jump[LG][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        deg[a[i]]++;
        wait[i]=INF;
        adj[a[i]].emplace_back(i);
    }
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        has[x]=true;
        wait[x]=0;
    }
    vector<int> q;
    for(int i=1;i<=n;i++)if(!deg[i])q.emplace_back(i);
    for(int i=0;i<q.size();i++){
        int u=q[i];
        int v=a[u];
        wait[v]=min(wait[v],wait[u]+1);
        if(--deg[v]==0)q.emplace_back(v);
    }
    vector<int> dep(n);
    int buf=0;
    for(int i=1;i<=n;i++)if(deg[i]==1&&!vis[i]){
        vector<int> p{i};
        for(int x=a[i];x!=i;x=a[x])p.emplace_back(x);
        for(auto x:p){
            vis[x]=true;
            wait[x]=1;
        }
        int sz=p.size();
        multiset<int> ms;
        for(int i=0;i<p.size();i++)if(has[p[i]]){
            ms.emplace(i);
            ms.emplace(i+sz);
        }
        for(int i=0;i<p.size();i++){
            int x=p[i];
            vector<int> qq{x},nodes;
            for(int d=0;!qq.empty();d++){
                int cur=-1;
                bool bad=false;
                vector<int> nq;
                for(auto u:qq){
                    nodes.emplace_back(u);
                    if(has[u]){
                        ans[u]=mx[0][u]=-1;
                        bad=true;
                        continue;
                    }
                    if(wait[u]<=n)qr[d+wait[u]-1].emplace_back(u,wait[u]);
                    else ans[u]=INF;
                    pos[u]=(i-d%sz+sz)%sz;
                    mx[0][u]=INF;
                    if(!ms.empty()){
                        auto it=ms.upper_bound(pos[u]+sz);
                        assert(it!=ms.begin());
                        mx[0][u]=pos[u]+sz-*prev(it)-1;
                    }
                }
                for(auto [u,k]:qr[d]){
                    ans[u]=-1;
                    for(int j=0;j<LG;j++)if(k>>j&1){
                        ans[u]=max(ans[u],mx[j][u]);
                        u=jump[j][u];
                    }
                }
                qr[d].clear();
                for(auto u:qq){
                    if(has[u]){
                        ms.emplace(pos[u]);
                        ms.emplace(pos[u]+sz);
                    }
                    for(auto v:adj[u])if(!vis[v]){
                        nq.emplace_back(v);
                        jump[0][v]=u;
                        for(int i=1;i<LG;i++){
                            jump[i][v]=jump[i-1][jump[i-1][v]];
                            mx[i][v]=max(mx[i-1][v],mx[i-1][jump[i-1][v]]);
                        }
                    }
                }
                qq=move(nq);
            }
            for(auto u:nodes)if(has[u]){
                ms.erase(ms.find(pos[u]));
                ms.erase(ms.find(pos[u]+sz));
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout << (ans[i]<=n?ans[i]:-2) << "\n";
    }
}