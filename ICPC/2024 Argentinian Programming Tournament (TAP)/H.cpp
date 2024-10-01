#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m;
int xl[N],xr[N],yl[N],yr[N];
int x[N],y[N];
vector<tuple<int,int,int>> event;
int a[N];
vector<int> adj[N];
ll ans;
map<int,int> mp;

void dfs(int u){
    for(auto v:adj[u]){
        dfs(v);
        a[u]+=a[v];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> xl[i] >> yl[i] >> xr[i] >> yr[i];
    }
    for(int i=1;i<=m;i++){
        cin >> x[i] >> y[i];
    }
    for(int i=1;i<=n;i++){
        event.emplace_back(yl[i],i,1);
        event.emplace_back(yr[i],i,2);
    }
    for(int i=1;i<=m;i++){
        event.emplace_back(y[i],i,3);
    }
    sort(event.begin(),event.end());
    mp[-1]=0;
    for(auto [y,i,t]:event){
        if(t==1){
            auto it=prev(mp.upper_bound(xl[i]));
            int v=it->second;
            mp[xl[i]]=i;
            mp[xr[i]]=v;
            adj[v].emplace_back(i);
        }else if(t==2){
            mp.erase(xl[i]);
            mp.erase(xr[i]);
        }else if(t==3){
            auto it=prev(mp.upper_bound(x[i]));
            a[it->second]++;
        }else{
            assert(false);
        }
    }
    dfs(0);
    for(int i=0;i<=n;i++){
        ans+=2LL*a[i]*(m-a[i]);
    }
    cout << fixed << setprecision(15) << 1.0*ans/m/m << "\n";
}