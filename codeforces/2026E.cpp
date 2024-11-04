#include "template.hpp"
#include "flow/binary-optimization.hpp"

void runcase(){
    int n;
    cin >> n;
    BinaryOptimization<ll,false> bo(n+60);
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    for(int i=0;i<n;i++){
        bo.add1(i,0,1);
    }
    for(int i=0;i<60;i++){
        bo.add1(n+i,0,-1);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<60;j++){
            if(a[i]>>j&1){
                bo.add2(i,n+j,0,0,-INF,0);
            }
        }
    }
    cout << bo.solve() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}