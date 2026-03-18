#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n;
    cin >> n;
    auto g=read_tree(n);
    HLD hld(g);
    int opt=1+g[0].size();
    vector<vector<int>> a(n);
    for(int i=0;i<n;i++)a[hld.dep[i]].emplace_back(i);
    for(int i=0;i<n;i++)opt=max(opt,(int)a[i].size());
    for(int i=1;i<n;i++)opt=max(opt,(int)g[i].size());
    vector<int> b(n,-1);
    set<int> s;
    for(int i=0;i<opt;i++)s.emplace(i);
    for(int i=n-1;i>=0;i--){
        vector<int> leaf,nonleaf,vals,temp;
        for(auto u:a[i]){
            int val=-1;
            for(auto v:g[u])if(v!=hld.par[u]){
                if(val==-1){
                    val=b[v];
                    vals.emplace_back(val);
                }else{
                    temp.emplace_back(b[v]);
                }
                s.erase(b[v]);
            }
            if(val!=-1){
                nonleaf.emplace_back(u);
            }else{
                leaf.emplace_back(u);
            }
        }
        int k=nonleaf.size();
        if(k==1){
            assert(!s.empty());
            int x=*s.begin();
            s.erase(s.begin());
            s.emplace(vals[0]);
            vals[0]=x;
        }
        for(int j=0;j<k;j++){
            b[nonleaf[j]]=vals[(j+1)%k];
        }
        for(auto x:temp)s.emplace(x);
        temp.clear();
        for(auto u:leaf){
            assert(!s.empty());
            int x=*s.begin();
            b[u]=x;
            temp.emplace_back(x);
            s.erase(s.begin());
        }
        for(auto x:vals)s.emplace(x);
        for(auto x:temp)s.emplace(x);
    }
    vector<vector<int>> ans(opt);
    for(int i=0;i<n;i++){
        assert(b[i]!=-1);
        ans[b[i]].emplace_back(i);
    }
    cout << opt << "\n";
    for(auto &v:ans){
        cout << v.size();
        for(auto x:v)cout << " " << x+1;
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}