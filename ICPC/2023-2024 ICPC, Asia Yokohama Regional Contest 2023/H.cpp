#include "template.hpp"
#include "flow/binary-optimization.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll p;
    cin >> n >> p;
    BinaryOptimization<ll,false> bo(n);
    vector<vector<ll>> a(2,vector<ll>(n)),b(2,vector<ll>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    for(auto &v:b){
        for(auto &x:v){
            cin >> x;
        }
    }
    for(int i=0;i<n;i++){
        bo.add1(i,p*b[0][i],p*b[1][i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            ll val0=max(a[0][i]*b[0][j],a[0][j]*b[0][i]);
            ll val1=max(a[1][i]*b[1][j],a[1][j]*b[1][i]);
            bo.add2(i,j,val0,0,0,val1);
        }
    }
    cout << bo.solve();
}