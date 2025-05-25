#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll n,k,p;
ll ans=0;
map<ll,int> cnt;    

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p >> k;
    if(k==0){
        for(int i=0;i<n;i++){
            ll x;
            cin >> x;
            if(x==0)ans=n-1;
        }
    }else{
        for(int i=0;i<n;i++){
            ll x;
            cin >> x;
            x=x*x%p*x%p;
            if(x!=0){
                ans+=cnt[k*binpow(x,p-2)%p];
                cnt[x]++;
            }
        }
    }
    cout << ans;
}