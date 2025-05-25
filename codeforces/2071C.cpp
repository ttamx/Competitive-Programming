#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n,s,t;
    cin >> n >> s >> t;
    s--,t--;
    auto g=read_tree(n);
    HLD hld(g,t);
    vector<int> a(n);
    iota(a.begin(),a.end(),0);
    sort(a.begin(),a.end(),[&](int i,int j){
        return hld.dep[i]>hld.dep[j];
    });
    for(auto x:a){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}