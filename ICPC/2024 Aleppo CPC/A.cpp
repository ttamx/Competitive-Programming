#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int MOD=1e9+7;

int n;
ll a[N];
ll dp[N];

struct Fenwick{
    ll t[N];
    void update(int x,ll v){
        for(int i=x+1;i<N;i+=i&-i){
            t[i]+=v;
        }
    }
    ll query(int x){
        ll res=0;
        for(int i=x+1;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    ll per=0;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        per+=a[i];
    }
    ll half=(per-1)/2;
    ll sum=0;
    dp[0]=1;
    f.update(0,1);
    for(int l=1,r=1;r<=n;r++){
        sum+=a[r];
        while(sum>half){
            sum-=a[l];
            l++;
        }
        dp[r]=((f.query(r-1)-f.query(l-2))%MOD+MOD)%MOD;
        f.update(r,dp[r]);
    }
    cout << dp[n];
}