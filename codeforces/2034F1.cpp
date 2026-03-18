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
    a.emplace_back(0,0);
    a.emplace_back(n,m);
    k+=2;
    sort(a.begin(),a.end());
    vector<vector<mint>> ways(k,vector<mint>(k));
    for(int i=0;i<k;i++){
        ways[i][i]=1;
    }
    for(int s=1;s<k;s++){
        for(int l=0,r=s;r<k;l++,r++){
            auto [xl,yl]=a[l];
            auto [xr,yr]=a[r];
            if(yl>yr)continue;
            ways[l][r]=comb.C(xr-xl+yr-yl,xr-xl);
            for(int i=l+1;i<r;i++){
                auto [xi,yi]=a[i];
                if(yi<yl||yi>yr)continue;
                ways[l][r]-=ways[l][i]*comb.C(xr-xi+yr-yi,xr-xi);
            }
        }
    }
    vector<mint> dp(k),dp2(k);
    for(int i=0;i<k;i++){
        auto [x,y]=a[i];
        for(int j=0;j<i;j++){
            auto [xx,yy]=a[j];
            if(yy>y)continue;
            int dx=x-xx,dy=y-yy;
            dp[i]+=(dp[j]+(dx*2+dy)*comb.C(xx+yy,xx))*ways[j][i]*2;
        }
    }
    cout << dp[k-1]/comb.C(n+m,n)/2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}