#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> u(m),v(m);
    DSU dsu(n);
    vector<vector<int>> comp(n);
    auto merge=[&](int u,int v){
        u=dsu.find(u),v=dsu.find(v);
        if(u==v)return false;
        if(comp[u].size()<comp[v].size()){
            swap(comp[u],comp[v]);
        }
        comp[u].insert(comp[u].end(),comp[v].begin(),comp[v].end());
        comp[v].clear();
        dsu.p[v]=u;
        return true;
    };
    for(int i=0;i<m;i++){
        cin >> u[i] >> v[i];
        u[i]--,v[i]--;
        if(!merge(u[i],v[i])){
            comp[dsu.find(u[i])].emplace_back(i);
        }
    }
    vector<pair<int,int>> a;
    for(int i=0;i<n;i++){
        if(dsu.find(i)==i){
            a.emplace_back(comp[i].size(),i);
        }
    }
    sort(a.rbegin(),a.rend());
    int cur=a[0].second;
    vector<int> ans;
    for(int i=1;i<a.size();i++){
        int j=a[i].second;
        int id=comp[cur].back();
        comp[cur].pop_back();
        ans.emplace_back(id);
        v[id]=j;
        merge(cur,j);
    }
    cout << ans.size() << "\n";
    for(auto i:ans){
        cout << i+1 << " " << u[i]+1 << " " << v[i]+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}