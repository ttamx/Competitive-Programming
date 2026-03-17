#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    DSU dsu(n);
    while(m--){
        int k;
        cin >> k;
        int st=-1;
        while(k--){
            int x;
            cin >> x;
            x--;
            if(st==-1){
                st=x;
            }else{
                dsu.merge(st,x);
            }
        }
    }
    for(int i=0;i<n;i++){
        cout << dsu.size(i) << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}