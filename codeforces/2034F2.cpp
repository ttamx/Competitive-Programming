#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<pair<int,int>> a(k);
    for(auto &[x,y]:a){
        cin >> x >> y;
        x=n-x,y=m-y;
    }
    k+=2;
    a.emplace_back(0,0);
    a.emplace_back(n,m);
    sort(a.begin(),a.end());
    vector<mint> dp(k);
    for(int i=0;i<k;i++){
        auto [x,y]=a[i];
        dp[i]=comb.C(x+y,x)*(x*2+y);
        for(int j=0;j<i;j++){
            auto [xx,yy]=a[j];
            if(yy>y)continue;
            int dx=x-xx,dy=y-yy;
            dp[i]+=dp[j]*comb.C(dx+dy,dx);
        }
    }
    cout << dp[k-1]/comb.C(n+m,n) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}