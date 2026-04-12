#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1005;

int n;
ll x[N],y[N],r[N];
vector<int> adj[N];
int col[N],bal;

bool dfs(int u){
    bool res=true;
    bal+=(col[u]?1:-1);
    for(auto v:adj[u]){
        if(col[v]==-1){
            col[v]=col[u]^1;
            if(!dfs(v))res=false;
        }else if(col[u]==col[v])res=false;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> x[i]>> y[i] >> r[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if((r[i]+r[j])*(r[i]+r[j])==(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])){
                adj[i].emplace_back(j);
                adj[j].emplace_back(i);
            }
        }
    }
    for(int i=1;i<=n;i++)col[i]=-1;
    for(int i=1;i<=n;i++){
        if(col[i]==-1){
            bal=0;
            col[i]=0;
            if(dfs(i)&&bal!=0){
                cout << "YES\n";
                exit(0);
            }
        }
    }
    cout << "NO\n";
}