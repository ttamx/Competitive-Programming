#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
long long k;
int p[N];
int sz[N],d[N],lv[N];
vector<int> adj[N];
vector<pair<int,int>> vec;
int ans[N];

void dfs(int u){
    sz[u]=1;
    for(auto v:adj[u]){
        lv[v]=lv[u]+1;
        dfs(v);
        sz[u]+=sz[v];
    }
    vec.emplace_back(lv[u]-sz[u]+1,u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> q;
    for(int i=2;i<=n;i++){
        cin >> p[i];
        adj[p[i]].emplace_back(i);
    }
    dfs(1);
    sort(vec.rbegin(),vec.rend());
    int cnt=1;
    cerr << k << "\n";
    for(auto [x,y]:vec){
        cerr << x << " ";
        if(x>k||x<0)continue;
        k-=x;
        ans[y]=cnt++;
    }
    cerr << "\n";
    cerr << k << "\n";
    if(k>0)cout << "TIDAK\n",exit(0);
    cout << "YA\n";
    for(int i=1;i<=n;i++)if(ans[i]==0)ans[i]=cnt++;
    for(int i=1;i<=n;i++)cout << ans[i] << " \n"[i==n];
}