#include <bits/stdc++.h>
using namespace std;

using ll=long long;

int main (){
    ios::sync_with_stdio(0); cin.tie(0);
    ll n,a,b;
    cin >> n >> a >> b;
    ll sum=0;
    for (ll i=1;i<=n;i++){
        ll nv=(n-i+1)*(n-i+2)/2;
        if(i%2==0){
            sum+=nv;
        }
        sum+=nv;
    }
    sum-= b*(a-b+1);
    for(ll l=1;l<=b;l++){
        ll r=min(a+1,n-a+l);
        sum-=max(0LL,r-b);
    }
    cout << sum;
}