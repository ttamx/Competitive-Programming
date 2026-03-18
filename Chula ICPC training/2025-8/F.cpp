#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=1e9+7;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    vector<ll> pw(n);
    pw[0]=1;
    for(int i=1;i<n;i++){
        pw[i]=pw[i-1]*10%MOD;
    }
    ll ans=0;
    for(int v=1;v<10;v++){
        int c=0;
        ll val=0;
        vector<ll> dp(n+1);
        vector<ll> ways(n+1);
        for(int i=0;i<n;i++){
            vector<ll> ndp(n+1);
            vector<ll> nways(n+1);
            for(int j=0;j<=n;j++){
                ndp[j]=(ndp[j]+dp[j]*v)%MOD;
                nways[j]=(nways[j]+ways[j]*v)%MOD;
                if(j+1<=n){
                    ndp[j+1]=(ndp[j+1]+dp[j]*10*(9-v))%MOD;
                    ndp[j+1]=(ndp[j+1]+dp[j]+ways[j]*pw[j])%MOD;
                    nways[j+1]=(nways[j+1]+ways[j]*(10-v))%MOD;
                }
            }
            int x=s[i]-'0';
            for(int d=0;d<x;d++){
                if(d<v){
                    ndp[c]=(ndp[c]+val)%MOD;
                    nways[c]=(nways[c]+1)%MOD;
                }else if(d>v){
                    ndp[c+1]=(ndp[c+1]+val*10)%MOD;
                    nways[c+1]=(nways[c+1]+1)%MOD;
                }else{
                    ndp[c+1]=(ndp[c+1]+val+pw[c])%MOD;
                    nways[c+1]=(nways[c+1]+1)%MOD;
                }
            }
            if(x>v){
                val=(val*10)%MOD;
                c++;
            }else if(x==v){
                val=(val+pw[c])%MOD;
                c++;
            }
            dp=move(ndp);
            ways=move(nways);
        }
        for(auto x:dp){
            ans=(ans+x*v)%MOD;
        }
    }
    sort(s.begin(),s.end());
    ll add=0;
    for(auto x:s){
        add=(add*10+x-'0')%MOD;
    }
    cout << (ans+add)%MOD << "\n";
}