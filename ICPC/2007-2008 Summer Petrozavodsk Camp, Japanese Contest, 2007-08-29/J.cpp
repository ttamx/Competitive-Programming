#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll euclid(ll a,ll b,ll &x,ll &y){
    x=1,y=0;
    ll x1=0,y1=1;
    while(b!=0){
        ll q=a/b;
        x-=q*x1;
        y-=q*y1;
        a-=q*b;
        swap(x,x1);
        swap(y,y1);
        swap(a,b);
    }
    return a;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n,m,a,k;
    while(cin >> n >> m >> a >> k){
        if(n==0&&m==0&&a==0&&k==0)break;
        ll x,y;
        ll g=euclid(a,-m,x,y);
        ll d=abs(n-k);
        if(d%g!=0){
            cout << "Impossible\n";
            continue;
        }
        x*=d/g;
        y*=d/g;
        ll s=m/g;
        if(x<=0){
            ll mul=abs(x)/s+1;
            x+=mul*s;
        }else{
            ll mul=(x-1)/s;
            x-=mul*s;
        }
        cout << a*x+k << "\n";
    }
}