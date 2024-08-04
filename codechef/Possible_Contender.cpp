#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    map<int,vector<int>> mp;
    for(int i=0;i<n;i++)mp[a[i]].emplace_back(i);
    DSU dsu(n);
    vector<bool> b(n);
    int small=0,big=n;
    auto update=[&](int i){
        b[i]=true;
        small++,big--;
        if(i>0&&b[i-1]&&dsu.merge(i,i-1))small--;
        if(i+1<n&&b[i+1]&&dsu.merge(i,i+1))small--;
    };
    vector<int> ans(n);
    for(auto &[_,v]:mp){
        if(big>small)for(auto x:v)ans[x]=1;
        for(auto x:v)update(x);
    }
    for(auto x:ans)cout << x;
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}