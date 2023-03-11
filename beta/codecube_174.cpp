#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1005;
const int M=2e5+5;
const int Q=10005;
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

int n,q;
pair<ll,ll> p[N],qr[Q];
Z ans[Q];
Z fac[M],inv[M];
Z dp[N];

Z C(int n,int r){
    return fac[n]*inv[n-r]*inv[r];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    fac[0]=1;
    for(int i=1;i<M;i++)fac[i]=fac[i-1]*i;
    inv[M-1]=binpow(fac[M-1],mod-2);
    for(int i=M-1;i>=1;i--)inv[i-1]=inv[i]*i;
    for(int i=1;i<=n;i++)cin >> p[i].first >> p[i].second;
    for(int i=1;i<=q;i++)cin >> qr[i].first >> qr[i].second,ans[i]=C(qr[i].first+qr[i].second-2,qr[i].first-1);
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++){
        auto [x,y]=p[i];
        dp[i]=C(x+y-2,x-1);
        for(int j=1;j<i;j++){
            auto [x2,y2]=p[j];
            if(y2>y)continue;
            dp[i]-=C(x+y-x2-y2,x-x2)*dp[j];
        }
        for(int j=1;j<=q;j++){
            auto [x2,y2]=qr[j];
            if(x>x2||y>y2)continue;
            ans[j]-=dp[i]*C(x2+y2-x-y,x2-x);
        }
    }
    for(int i=1;i<=q;i++)cout << ans[i].x << '\n';
}