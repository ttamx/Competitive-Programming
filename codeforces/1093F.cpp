#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,k,len;
    cin >> n >> k >> len;
    vector<int> a(n+1);
    vector<vector<int>> cnt(n+1,vector<int>(k));
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]>0){
            a[i]--;
            cnt[i][a[i]]++;
        }else{
            for(int j=0;j<k;j++){
                cnt[i][j]++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            cnt[i][j]+=cnt[i-1][j];
        }
    }
    vector<vector<mint>> dp(n+1,vector<mint>(k));
    vector<mint> aux(n+1);
    aux[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            if(a[i]==-1||a[i]==j){
                dp[i][j]=aux[i-1];
                if(i>=len&&cnt[i][j]-cnt[i-len][j]==len){
                    dp[i][j]-=aux[i-len]-dp[i-len][j];
                }
            }
            aux[i]+=dp[i][j];
        }
    }
    cout << aux[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}