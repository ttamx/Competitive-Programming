#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<mint> a(n);
    for(auto &x:a)cin >> x;
    reverse(a.begin(),a.end());
    int k=29;
    vector<int> b(k);
    for(int i=0;i<n;i++){
        mint v=1;
        for(int j=0;j<k;j++){
            a[i]-=v*comb.C(b[j],n-i);
            v*=2;
        }
        v=1;
        int x=a[i].val();
        for(int j=0;j<k;j++){
            if(x>>j&1){
                assert(!b[j]);
                b[j]=n-i;
                a[i]-=v*comb.C(b[j],n-i);
            }
            v*=2;
        }
        assert(a[i].val()==0);
    }
    vector<int> ans(n);
    for(int i=0;i<k;i++){
        for(int j=0;j<b[i];j++){
            ans[j]|=1<<i;
        }
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}