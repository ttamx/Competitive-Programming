#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

const int N=1e5+5;

mint pw25[N],pw26[N];

void runcase(){
    int q;
    cin >> q;
    string s;
    cin >> s;
    int k=s.size();
    map<int,array<mint,N>> ans;
    pw25[0]=1;
    pw26[0]=1;
    for(int i=1;i<N;i++){
        pw25[i]=pw25[i-1]*25;
        pw26[i]=pw26[i-1]*26;
    }
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            cin >> s;
            k=s.size();
            continue;
        }
        int n;
        cin >> n;
        if(!ans.count(k)){
            array<mint,N> dp{};
            dp[k]=1;
            for(int i=k+1;i<N;i++){
                dp[i]=dp[i-1]*26+comb.C(i-1,k-1)*pw25[i-k];
            }
            ans[k]=move(dp);
        }
        cout << ans[k][n] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}