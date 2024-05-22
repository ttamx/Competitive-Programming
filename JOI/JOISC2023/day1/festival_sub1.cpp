#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int n,p;
ll ans;
vector<int> v;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    assert(n<=8);
    v.resize(2*n);
    iota(v.begin(),v.end(),1);
    do{
        bool ok=true;
        vector<int> a(11);
        for(int i=0;i<2*n;i+=2){
            if(i>0&&v[i]<v[i-2])ok=false;
            if(v[i+1]<v[i])ok=false;
            a[v[i+1]]=v[i];
        }
        if(!ok)continue;
        vector<int> dp(2*n+1);
        for(int i=1;i<=2*n;i++){
            dp[i]=dp[i-1];
            if(a[i])dp[i]=max(dp[i],dp[a[i]]+1);
        }
        dp[2*n]--;
        int st=v[1],idx=2;
        while(st<2*n&&idx<2*n){
            while(idx<2*n&&v[idx]<=st)idx+=2;
            if(idx<2*n){
                dp[2*n]--;
                st=v[idx+1];
            }
        }
        if(dp[2*n]>0){
            ans++;
        }
    }while(next_permutation(v.begin(),v.end()));
    cout << ans;
}