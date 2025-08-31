#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    mint base=1;
    if(a[0]==-1)base*=k;
    if(b[n-1]==-1)base*=k;
    vector<mint> dp(n*k+1);
    dp[n*k]=1;
    for(int i=0;i+1<n;i++){
        vector<mint> ndp(n*k+1);
        mint ways=0;
        for(auto x:dp)ways+=x;
        if(a[i+1]==-1&&b[i]==-1){
            for(int d=1;d<=k;d++){
                ndp[d]+=ways*(k-d);
            }
            vector<mint> aux(n*k+k+1),aux2(n*k+k+1);
            for(int j=0;j<=n*k;j++){
                aux[j]+=dp[j];
                aux[j+k]-=dp[j];
                aux2[j+k]-=dp[j]*k;
            }
            mint slope=0,cur=0;
            for(int j=0;j<=n*k+k-1;j++){
                slope+=aux[j];
                cur+=slope+aux2[j];
                if(j>=k-1){
                    ndp[j-k+1]+=cur;
                }
            }
            ways*=k*(k+1)/2;
        }else if(a[i+1]==-1){
            for(int d=1;d<=b[i]-1;d++){
                ndp[d]+=ways;
            }
            vector<mint> aux(n*k+k+2);
            int l=b[i]-k;
            for(int j=0;j<=n*k;j++){
                aux[j+k+l]+=dp[j];
                aux[j+k+1]-=dp[j];
            }
            mint cur=0;
            for(int j=0;j<=n*k+k;j++){
                cur+=aux[j];
                if(j>=k){
                    ndp[j-k]+=cur;
                }
            }
        }else if(b[i]==-1){
            for(int d=1;d<=k-a[i+1];d++){
                ndp[d]+=ways;
            }
            vector<mint> aux(n*k+k+2);
            int l=1-a[i+1];
            for(int j=0;j<=n*k;j++){
                aux[j+k+l]+=dp[j];
                aux[j+k+1]-=dp[j];
            }
            mint cur=0;
            for(int j=0;j<=n*k+k;j++){
                cur+=aux[j];
                if(j>=k){
                    ndp[j-k]+=cur;
                }
            }
        }else{
            if(a[i+1]<b[i]){
                ndp[b[i]-a[i+1]]+=ways;
            }
            int d=b[i]-a[i+1];
            for(int j=0;j<=n*k;j++){
                if(0<=j+d&&j+d<=n*k){
                    ndp[j+d]+=dp[j];
                }
            }
        }
        dp=move(ndp);
    }
    mint ans=0;
    for(auto x:dp)ans+=x;
    cout << base*ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}