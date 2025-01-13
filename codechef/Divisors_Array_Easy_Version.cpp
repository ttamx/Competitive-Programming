#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=1e5+5;

int lp[N];

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> cnt(m+1);
    for(int i=1;i<=m;i++){
        int x=i;
        while(x>1){
            cnt[lp[x]]++;
            x/=lp[x];
        }
    }
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        map<int,int> dp;
        for(int j=1;j<=m;j++){
            if(cnt[j]){
                dp[j]=cnt[j];
            }
        }
        while(x>1){
            dp[lp[x]]++;
            x/=lp[x];
        }
        mint ans=1;
        for(auto [_,v]:dp){
            ans*=v+1;
        }
        cout << ans << " ";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(lp[i]==0){
            for(int j=i;j<N;j+=i){
                if(lp[j]==0){
                    lp[j]=i;
                }
            }
        }
    }
    int t(1);
    while(t--)runcase();
}