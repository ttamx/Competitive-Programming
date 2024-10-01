#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    if(m==0){
        cout << 1;
        return;
    }
    vector<int> pos{0};
    vector<pair<int,int>> a(m);
    for(auto &[u,v]:a){
        cin >> u >> v;
        u--,v--;
        pos.emplace_back(u);
        pos.emplace_back(v);
    }
    sort(pos.begin(),pos.end());
    pos.erase(unique(pos.begin(),pos.end()),pos.end());
    m=pos.size();
    vector<vector<pair<int,int>>> adj(m);
    for(auto [u,v]:a){
        u=lower_bound(pos.begin(),pos.end(),u)-pos.begin();
        v=lower_bound(pos.begin(),pos.end(),v)-pos.begin();
        adj[u].emplace_back(v,1);
    }
    vector<int> d(m);
    for(int i=0;i<m;i++){
        d[i]=pos[(i+1)%m]-pos[i];
        if(d[i]<0)d[i]+=n;
        adj[i].emplace_back((i+1)%m,d[i]);
    }
    vector<vector<mint>> dp(k+1,vector<mint>(m));
    dp[0][0]=1;
    mint ans=0;
    for(int i=0;i<=k;i++){
        for(int j=0;j<m;j++){
            for(auto [v,w]:adj[j]){
                if(i+w<=k){
                    dp[i+w][v]+=dp[i][j];
                }
            }
            if(i+d[j]>k){
                ans+=dp[i][j];
            }
        }
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}