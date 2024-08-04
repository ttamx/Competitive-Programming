#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,k,m;
    cin >> n >> k >> m;
    vector<int> fib(25+1);
    fib[0]=0,fib[1]=1;
    for(int i=2;i<=25;i++)fib[i]=fib[i-1]+fib[i-2];
    int tot=fib[10]*n;
    vector<int> opt(tot+1);
    for(int i=0;i<=tot;i++){
        opt[i]=i;
        for(int j=1;j<=25;j++){
            if(fib[j]>i)break;
            opt[i]=min(opt[i],opt[i-fib[j]]+1);
        }
    }
    vector<vector<mint>> dp(k+1,vector<mint>(tot+1));
    dp[0][0]=1;
    for(int i=0;i<n;i++){
        vector<vector<mint>> ndp(k+1,vector<mint>(tot+1));
        for(int j=1;j<=k;j++){
            int f=fib[j];
            for(int x=0;x<=tot;x++){
                dp[j][x]+=dp[j-1][x];
            }
            for(int x=f;x<=tot;x++){
                ndp[j][x]=dp[j][x-f];
            }
        }
        swap(dp,ndp);
    }
    mint ans=0;
    for(int j=1;j<=k;j++){
        for(int i=1;i<=tot;i++){
            if(opt[i]==m){
                ans+=dp[j][i];
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}