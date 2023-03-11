#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3005;
const int M=2e5+5;
const ll mod=1e9+7;

template<typename T>
T binpow(T a,ll b){
    T res=1;
    while(b){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

struct Z{
    ll x;
    Z():x(0){}
    Z(ll x):x(x){}
    Z& operator+=(Z o){x=(x+o.x)%mod;return *this;}
    Z& operator-=(Z o){x=(x+mod-o.x)%mod;return *this;}
    Z& operator*=(Z o){x=(x*o.x)%mod;return *this;}
    Z& operator/=(Z o){return *this*=binpow(o,mod-2);}
    friend Z operator+(Z a,Z b){return a+=b;}
    friend Z operator-(Z a,Z b){return a-=b;}
    friend Z operator*(Z a,Z b){return a*=b;}
    friend Z operator/(Z a,Z b){return a/=b;}
};

int n;
ll h,w;
pair<ll,ll> p[N];
Z ans;
Z fac[M],inv[M];
Z dp[N];

Z C(int n,int r){
    return fac[n]*inv[n-r]*inv[r];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> h >> w >> n;
    fac[0]=1; 
    for(int i=1;i<=h+w;i++)fac[i]=fac[i-1]*i;
    inv[h+w]=binpow(fac[h+w],mod-2);
    for(int i=h+w;i>=1;i--)inv[i-1]=inv[i]*i;
    ans=C(h+w-2,h-1);
    for(int i=1;i<=n;i++)cin >> p[i].first >> p[i].second;
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++){
        auto [x,y]=p[i];
        dp[i]=C(x+y-2,x-1);
        for(int j=1;j<i;j++){
            auto [x2,y2]=p[j];
            if(y2>y)continue;
            dp[i]-=C(x+y-x2-y2,x-x2)*dp[j];
        }
        ans-=dp[i]*C(h+w-x-y,h-x);
    }
    cout << ans.x;
}