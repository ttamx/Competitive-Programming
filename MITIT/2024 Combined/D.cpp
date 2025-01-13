#include <bits/stdc++.h>

using namespace std;

int c;

void runcase(){
    int n;
    cin >> n;
    vector<int> deg(n+1);
    vector<vector<int>> adj(n+1);
    vector<int> close(n+1,-1);
    vector<bool> alive(n+1,true);
    vector<int> a(n+1);
    int ans=n+1;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]--;
        deg[a[i]]++,deg[i]++;
        adj[a[i]].emplace_back(i);
        adj[i].emplace_back(a[i]);
        if(deg[a[i]]==3){
            close[i]=a[i];
            alive[a[i]]=false;
            ans--;
        }
    }
    vector<int> p(n+1),sz(n+1,1);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    };
    auto merge=[&](int u,int v){
        u=fp(u),v=fp(v);
        assert(u!=v);
        ans-=(sz[u]+1)/2;
        ans-=(sz[v]+1)/2;
        p[v]=u;
        sz[u]+=sz[v];
        ans+=(sz[u]+1)/2;
    };
    for(int i=1;i<=n;i++){
        if(alive[i]&&alive[a[i]]){
            merge(i,a[i]);
        }
    }
    vector<int> output{ans};
    if(c){
        for(int i=n;i>=2;i--){
            int r=fp(i);
            ans-=(sz[r]+1)/2;
            sz[r]--;
            ans+=(sz[r]+1)/2;
            if(close[i]!=-1){
                alive[close[i]]=true;
                ans++;
                for(auto j:adj[close[i]]){
                    if(alive[j]){
                        merge(close[i],j);
                    }
                }
            }
            output.emplace_back(ans);
        }
    }
    reverse(output.begin(),output.end());
    for(auto x:output){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t >> c;
    while(t--)runcase();
}