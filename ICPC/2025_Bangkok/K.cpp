#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll floor(ll a,ll b){
    return a/b-((a^b)<0&&a%b);
}

ll mod(ll a,ll b){
    return (a%b+b)%b;
}

ll euclid(ll a,ll b,ll &x,ll &y){
	if(!b)return x=1,y=0,a;
	ll d=euclid(b,a%b,y,x);
	return y-=a/b*x,d;
}

ll crt(ll a,ll m,ll b,ll n){
    a=mod(a,m);
    b=mod(b,n);
	if(n>m)swap(a,b),swap(m,n);
	ll x,y,g=euclid(m,n,x,y);
	if((a-b)%g!=0)return -1LL;
	x=(b-a)%n*x%n/g*m+a;
	return x<0?x+m*n/g:x;
}

ll floor_sum(ll a,ll b,ll c,ll n){
    ll res=n*(n+1)/2*floor(a,c)+(n+1)*floor(b,c);
    a=mod(a,c),b=mod(b,c);
    if(a==0)return res;
    ll m=floor(a*n+b,c);
    return res+n*m-floor_sum(c,c-b-1,a,m-1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll x,y,n,m;
        cin >> x >> y >> n >> m;
        x--,y--,n--,m--;
        ll t=crt(-x,n,-y,m);
        if(t==-1){
            cout << -1 << "\n";
        }else{
            cout << t+1-floor_sum(-m,t,n,t/m)+t/n << "\n";
        }
    }
}