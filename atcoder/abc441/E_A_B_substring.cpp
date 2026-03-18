#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    vector<int> a;
    for(auto x:s){
        if(x=='A')a.emplace_back(1);
        else if(x=='B')a.emplace_back(-1);
        else a.emplace_back(0);
    }
    ll ans=0;
    int bal=n;
    Fenwick<int> f(2*n+1);
    f.update(n,+1);
    for(auto x:a){
        bal+=x;
        ans+=f.query(bal-1);
        f.update(bal,+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}