#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll len;
int n,m;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%m;
        a=a*a%m;
        b>>=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> len >> n >> m;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    priority_queue<ll> pq;
    if(a[0]!=1)pq.emplace(1);
    for(auto x:a)pq.emplace(x);
    ll ans=binpow(2,len-pq.top());
    ll p=0;
    len=pq.top();
    pq.pop();
    while(true){
        if(p*2>len){
            pq.emplace(len-p);
            p=0;
        }
        if(pq.empty())break;
        ll x=pq.top();
        pq.pop();
        if(!x)break;
        if(x*2>len){
            p=gcd(p,len-x);
        }else if(!p){
            ans=ans*binpow(2,(len+1)/2-x)%m;
            len=x;
        }else{
            ll t=(len-max(x,p))/p;
            len-=t*p;
            pq.emplace(x);
        }
    }
    cout << ans*2%m << "\n";
}