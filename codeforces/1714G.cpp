#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll,ll,ll> t3;

void runcase(){
    int n;
    cin >> n;
    vector<vector<ll>> adj(n+1);
    vector<int> lv(n+1);
    vector<array<ll,20>> pa(n+1),sa(n+1),sb(n+1);
    for(int i=2;i<=n;i++){
        int p,a,b;
        cin >> p >> a >> b;
        adj[p].push_back(i);
        pa[i][0]=p;
        sa[i][0]=a;
        sb[i][0]=b;
    }
    function<void(int)> dfs=[&](int u){
        for(int i=1;i<20;i++){
            pa[u][i]=pa[pa[u][i-1]][i-1];
            sa[u][i]=sa[u][i-1]+sa[pa[u][i-1]][i-1];
            sb[u][i]=sb[u][i-1]+sb[pa[u][i-1]][i-1];
        }
        for(auto v:adj[u]){
            lv[v]=lv[u]+1;
            dfs(v);
        }
    };
    dfs(1);
    for(int i=2;i<=n;i++){
        ll A=sa[i][19],B=sb[i][19];
        ll dif=B-A;
        if(dif<=0){
            cout << lv[i] << ' ';
            continue;
        }
        int cur=i;
        for(int j=19;j>=0;j--){
            if(sb[cur][j]>=dif)continue;
            dif-=sb[cur][j];
            cur=pa[cur][j];
        }
        cur=pa[cur][0];
        cout << lv[cur] << ' ';
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}