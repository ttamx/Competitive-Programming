#include<bits/stdc++.h>
#define ll long long
#define y0 Y

using namespace std;

ll n,x0,y0;

bool examine(ll x,ll y){
    if(x<1||y<1||x>n||y>n)return 0;
    cout << "examine " << x << " " << y << endl;
    string ret;
    cin >> ret;
    return (ret=="true");
}

ll furthest(ll x,ll y){
    ll i=0;
    while(examine(x0+(x<<i),y0+(y<<i)))++i;
    ll l=0,r=1<<i;
    if(i)l=1<<(i-1);
    while(l+1<r){
        ll m=(l+r)>>1;
        if(examine(x0+m*x,y0+m*y))l=m;
        else r=m;
    }
    return l;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> x0 >> y0;
    ll L=x0-furthest(-1,0);
    ll R=x0+furthest(1,0);
    ll B=y0-furthest(0,-1);
    ll U=y0+furthest(0,1);
    ll m=R-L+1;
    m*=2;
    while(examine(L-m,y0))L-=m;
    while(examine(R+m,y0))R+=m;
    while(examine(x0,B-m))B-=m;
    while(examine(x0,U+m))U+=m;
    cout << "solution " << (L+R)/2 << " " << (U+B)/2;
}