#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> p(n),a(n);
    for(auto &x:p)cin >> x,x--;
    for(auto &x:a)cin >> x,x--;
    reverse(a.begin(),a.end());
    vector<bool> f(n);
    int base=n;
    vector<int> ans;
    DSU dsu(n);
    for(auto i:a){
        ans.emplace_back(base);
        f[i]=true;
        dsu.merge(p[i],i);
        if(f[dsu.find(p[i])])base-=dsu.size(i);
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}