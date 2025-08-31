#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<int,vector<int>> pos;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        pos[-x].emplace_back(i);
    }
    pos[0];
    vector<int> fa(n),sz(n,1);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u)->int {
        return fa[u]=u==fa[u]?u:fp(fa[u]); 
    };
    auto calc=[&](int s){
        return (s+1)/2;
    };
    ll last=-2e9;
    ll coef=0;
    ll ans=0;
    auto merge=[&](int u,int v){
        u=fp(u),v=fp(v);
        assert(u!=v);
        coef-=calc(sz[u]);
        coef-=calc(sz[v]);
        sz[u]+=sz[v];
        fa[v]=u;
        coef+=calc(sz[u]);
    };
    vector<bool> alive(n);
    for(auto &[val,vec]:pos){
        ll diff=val-last;
        ans+=coef*diff;
        for(auto i:vec){
            alive[i]=true;
            coef++;
            if(i>0&&alive[i-1]){
                merge(i-1,i);
            }
            if(i+1<n&&alive[i+1]){
                merge(i,i+1);
            }
        }
        last=val;
    }
    cout << ans << "\n";
}