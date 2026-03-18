#include "template.hpp"
#include "data-structure/dsu.hpp"

const int N=1005;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    set<int> a;
    DSU dsu(2*N);
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        y+=N;
        dsu.merge(x,y);
        a.emplace(x);
        a.emplace(y);
    }
    int cnt=0;
    for(auto x:a){
        if(dsu.find(x)==x){
            cnt++;
        }
    }
    cout << cnt-1 << "\n";
}