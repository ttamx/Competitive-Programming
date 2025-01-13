#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int B=60;
const ll MOD=1e9+7;

int n,m;
pair<int,int> edges[N];
vector<int> adj[N];
bool vis1[N],vis2[N];
int ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        auto &[u,v]=edges[i];
        cin >> u >> v;
        adj[v].emplace_back(u);
        adj[u].emplace_back(v);
    }
    vis1[1]=true;
    for(int i=1;i<=n;i++){
        if(vis1[i]){
            for(auto j:adj[i]){
                if(j>i){
                    vis1[j]=true;
                }
            }
        }
    }
    if(!vis1[n]){
        cout << 0;
        exit(0);
    }
    vis2[n]=true;
    for(int i=n;i>=1;i--){
        if(vis2[i]){
            for(auto j:adj[i]){
                if(j<i){
                    vis2[j]=true;
                }
            }
        }
    }
    for(int i=1;i<=m;i++){
        auto [u,v]=edges[i];
        if(vis1[u]&&vis2[u]&&vis1[v]&&vis2[v]){
            ans++;
        }
    }
    for(int i=1;i<=n;i++){
        if(vis1[i]&&vis2[i]){
            ans--;
        }
    }
    cout << ans+2 << "\n";
}