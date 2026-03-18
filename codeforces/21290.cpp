#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    DSU dsu(2*n);
    vector<int> ans;
    for(int i=0;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(dsu.merge(u,v)){
            ans.emplace_back(i);
        }
    }
    cout << ans.size() << "\n";
    for(auto x:ans){
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