#include<bits/stdc++.h>

using namespace std;

const int N=2e6+5;

int n,q;
int p[N],a[N],dep[N];
vector<int> adj[N];
int b[N];
bool vis[N];

vector<tuple<int,int,int>> event;

void dfs(int u){
    vis[u]=true;
    for(auto v:adj[u]){
        dfs(v);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=2;i<=n;i++){
        cin >> p[i];
        adj[p[i]].emplace_back(i);
        dep[i]=dep[p[i]]+1;
    }
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int x,y;
            cin >> x >> y;
            event.emplace_back(1,x,y);
        }else if(t==2){
            int u,x;
            cin >> u >> x;
            event.emplace_back(2,u,x);
        }else{
            int u;
            cin >> u;
            for(int i=0;i<=n;i++){
                vis[i]=false;
                b[i]=0;
            }
            dfs(u);
            for(int i=1;i<=n;i++){
                if(vis[i]){
                    b[dep[i]]+=a[i];
                }
            }
            for(auto [t,x,y]:event){
                if(t==1){
                    b[y]+=b[x];
                    b[x]=0;
                }else{
                    if(vis[x]){
                        b[dep[x]]+=y;
                    }
                }
            }
            cout << b[dep[u]] << "\n";
        }
    }
}