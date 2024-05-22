#include<bits/stdc++.h>
#define all(x) begin(x),end(x)

using namespace std;

const int N=2e5+5;
const int K=405;
const int M=505;

int n,r,q,cnt;
int a[N],id[N];
long long dp[M][N];
vector<int> adj[N],comp[N],comp2[N];
int tin[N],tout[N];
int timer;

void tour(int u){
    tin[u]=++timer;
    comp2[a[u]].emplace_back(timer);
    for(auto v:adj[u])tour(v);
    tout[u]=timer;
}

void dfs(int u,int i,int c=0){
    if(a[u]==i)c++;
    else dp[id[i]][a[u]]+=c;
    for(auto v:adj[u])dfs(v,i,c);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> r >> q;
    for(int i=1;i<=n;i++){
        if(i>1){
            int p;
            cin >> p;
            adj[p].emplace_back(i);
        }
        cin >> a[i];
        comp[a[i]].emplace_back(i);
    }
    tour(1);
    for(int i=1;i<=r;i++)if(comp[i].size()>K){
        id[i]=++cnt;
        dfs(1,i);
    }
    while(q--){
        int r1,r2;
        cin >> r1 >> r2;
        if(id[r1])cout << dp[id[r1]][r2] << endl;
        else{
            long long ans=0;
            for(auto u:comp[r1])ans+=upper_bound(all(comp2[r2]),tout[u])-lower_bound(all(comp2[r2]),tin[u]);
            cout << ans << endl;
        }
    }
}