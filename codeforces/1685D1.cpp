#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> p(n),inv(n);
    for(auto &x:p){
        cin >> x;
        x--;
    }
    for(int i=0;i<n;i++){
        inv[p[i]]=i;
    }
    DSU dsu(n);
    for(int i=0;i<n;i++){
        for(int j=i;dsu.merge(j,p[j]);j=p[j]);
    }
    for(int i=0;i<n-1;i++){
        if(dsu.merge(i,i+1)){
            swap(p[inv[i]],p[inv[i+1]]);
            swap(inv[i],inv[i+1]);
        }
    }
    vector<int> q(n);
    q[0]=0;
    for(int i=0;i<n-1;i++){
        q[i+1]=inv[q[i]];
    }
    for(auto x:q){
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