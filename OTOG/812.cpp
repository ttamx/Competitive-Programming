#include "template/Header.hpp"
#include "Graph/MinCostFlow.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    MinCostFlow<ll,ll> mcf(n*2+2);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int x;
            cin >> x;
            mcf.addEdge(i,j+n,1,x);
        }
    }
    for(int i=0;i<n;i++){
        mcf.addEdge(n*2,i,1,0);
        mcf.addEdge(i+n,n*2+1,1,0);
    }
    cout << mcf.flow(n*2,n*2+1).second;
}