#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    if(a[0]!=1){
        cout << "0\n";
        return;
    }
    for(int i=1;i<n;i++){
        if(a[i]>a[i-1]+1){
            cout << "0\n";
            return;
        }
    }
    vector<pair<int,int>> par(n,{-1,0});
    vector<vector<pair<int,int>>> adj(n);
    vector<int> s{0};
    for(int i=1;i<n;i++){
        int last=-1;
        while(s.size()+1>a[i]){
            last=s.back();
            s.pop_back();
        }
        if(last!=-1){
            par[last]={i,1};
        }
        if(!s.empty()){
            par[i]={s.back(),0};
        }
        s.emplace_back(i);
    }
    int root=-1;
    for(int i=0;i<n;i++){
        if(par[i].first==-1){
            assert(root==-1);
            root=i;
        }else{
            adj[par[i].first].emplace_back(i,par[i].second);
        }
    }
    vector<vector<mint>> dp(n,vector<mint>(k+1));
    function<void(int)> dfs=[&](int u){
        for(int i=1;i<=k;i++){
            dp[u][i]=1;
        }
        for(auto [v,w]:adj[u]){
            dfs(v);
            for(int i=1;i<=k;i++){
                dp[u][i]*=dp[v][i-w];
            }
        }
        for(int i=1;i<=k;i++){
            dp[u][i]+=dp[u][i-1];
        }
    };
    dfs(root);
    cout << dp[root][k] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}