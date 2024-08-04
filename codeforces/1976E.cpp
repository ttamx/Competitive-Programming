#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> l(q),r(q);
    for(auto &x:l)cin >> x;
    for(auto &x:r)cin >> x;
    vector<int> id(n+1,-1);
    vector<int> lch,rch,val;
    int m=0;
    auto new_node=[&](int x){
        lch.emplace_back(-1);
        rch.emplace_back(-1);
        val.emplace_back(x);
        return id[x]=m++;
    };
    new_node(n);
    for(int i=0;i<q;i++){
        if(id[l[i]]!=-1){
            int u=id[l[i]];
            lch[u]=new_node(l[i]);
            rch[u]=new_node(r[i]);
        }else{
            int u=id[r[i]];
            lch[u]=new_node(l[i]);
            rch[u]=new_node(r[i]);
        }
    }
    vector<int> a;
    function<void(int)> dfs=[&](int u){
        if(lch[u]==-1)return void(a.emplace_back(val[u]));
        dfs(lch[u]);
        dfs(rch[u]);
    };
    dfs(0);
    vector<bool> leaf(n+1);
    for(auto x:a)leaf[x]=true;
    vector<int> cnt(n+1);
    for(int i=0;i+1<a.size();i++){
        cnt[max(a[i],a[i+1])]++;
    }
    cnt[a[0]]++;
    cnt[a.back()]++;
    mint ans=1,pos=0;
    for(int i=n;i>=1;i--){
        pos+=cnt[i];
        if(leaf[i])continue;
        ans*=pos;
        pos++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}