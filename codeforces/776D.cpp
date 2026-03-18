#include "template.hpp"
#include "data-structure/dsu.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> s(n);
    for(auto &x:s){
        cin >> x;
    }
    vector<vector<int>> a(n);
    for(int i=0;i<m;i++){
        int k;
        cin >> k;
        while(k--){
            int x;
            cin >> x;
            x--;
            a[x].emplace_back(i);
        }
    }
    DSU dsu(m*2);
    for(int i=0;i<n;i++){
        assert(a[i].size()==2);
        if(s[i]){
            dsu.merge(a[i][0],a[i][1]);
            dsu.merge(a[i][0]+m,a[i][1]+m);
        }else{
            dsu.merge(a[i][0],a[i][1]+m);
            dsu.merge(a[i][0]+m,a[i][1]);
        }
    }
    for(int i=0;i<m;i++){
        if(dsu.same(i,i+m)){
            cout << "NO\n";
            exit(0);
        }
    }
    cout << "YES\n";
}