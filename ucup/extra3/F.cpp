#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    ll c=0;
    array<ll,2> dp{1,0};
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x){
            c++;
        }else{
            array<ll,2> ndp{0,0};
            for(int e=0;e<2;e++){
                ndp[e]=c*(c-1+e)%MOD*dp[e]%MOD;
            }
            if(c>0){
                ndp[1]=(ndp[1]+dp[0]*c)%MOD;
            }
            c--;
            dp=move(ndp);
        }
    }
    cout << dp[n&1^1];
}