#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> p(n),col(n);
    vector<vector<int>> comp(n);
    for(int i=0;i<n;i++){
        p[i]=i;
        comp[i].emplace_back(i);
    }
    bool ok=true;
    function<int(int)> fp=[&](int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    };
    auto uni=[&](int u,int v){
        int pu=fp(u),pv=fp(v);
        if(pu==pv){
            if(col[u]==col[v]){
                ok=false;
            }
            return;
        }
        if(comp[pu].size()<comp[pv].size()){
            swap(u,v),swap(pu,pv);
        }
        if(col[u]==col[v]){
            for(auto x:comp[pv]){
                col[x]^=1;
            }
        }
        comp[pu].insert(comp[pu].end(),comp[pv].begin(),comp[pv].end());
        comp[pv].clear();
        p[pv]=pu;
    };
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        uni(u,v);
        if(!ok){
            cout << i;
            exit(0);
        }
    }
    cout << m;
}