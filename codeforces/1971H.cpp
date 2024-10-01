#include "template.hpp"
#include "graph/graph-base.hpp"
#include "graph/strongly-connected-component.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<array<int,3>> a(n);
    for(int i=0;i<3;i++){
        for(int j=0;j<n;j++){
            cin >> a[j][i];
        }
    }
    auto get_id=[&](int x){
        return x>0?x-1:n-x-1;
    };
    Graph<void,true> g(2*n);
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                if(k!=j){
                    g.add_edge(get_id(-a[i][j]),get_id(a[i][k]));
                }
            }
        }
    }
    auto scc=strongly_connected_component(g).second;
    for(int i=0;i<n;i++){
        if(scc[i]==scc[i+n]){
            return void(cout << "NO\n");
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}