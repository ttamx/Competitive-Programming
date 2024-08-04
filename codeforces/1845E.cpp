#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    const int m=60;
    vector dp(2*m+1,vector<mint>(k+1));
    dp[m][0]=1;
    for(auto x:a){
        vector ndp(2*m+1,vector<mint>(k+1));
        for(auto y:{0,1}){
            int d=x-y;
            for(int i=-m;i<=m;i++){
                int ni=i+d;
                if(ni<-m||m<ni)continue;
                for(int j=0;j<=k;j++){
                    int nj=j+abs(ni);
                    if(nj>k)continue;
                    ndp[ni+m][nj]+=dp[i+m][j];
                }
            }
        }
        swap(dp,ndp);
    }
    mint ans=0;
    for(int i=k;i>=0;i-=2)ans+=dp[m][i];
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}