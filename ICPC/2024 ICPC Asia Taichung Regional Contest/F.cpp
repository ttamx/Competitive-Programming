#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N=1e6+5;
const ll INF=1e18;

ll modmul(ll a, ll b, ll M) {
	ll ret = a * b - M * ll(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ll modpow(ll b, ll e, ll mod) {
	ll ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool is_prime(ll n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ll a : A) {   // ^ count trailing zeroes
		ll p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

void solve(){
    ll st,ed;
    cin >> st >> ed;
    st*=2,ed*=2;
    ll len=INF,cnt=0;
    int n=ed-st+1;
    vector<bool> pr(n);
    vector<ll> dpl(n),dpr(n);
    for(int i=0;i<n;i++){
        pr[i]=is_prime(st+i);
    }
    dpl[0]=pr[0]?0:-INF;
    for(int i=1;i<n;i++){
        dpl[i]=pr[i]?i:dpl[i-1];
    }
    dpr[n-1]=pr[n-1]?n-1:INF;
    for(int i=n-2;i>=0;i--){
        dpr[i]=pr[i]?i:dpr[i+1];
    }
    function<void(ll,ll)> rec=[&](ll l,ll r){
        if(r-l<len){
            len=r-l;
            cnt=1;
        }else if(r-l==len){
            cnt++;
        }
        ll v=dpl[(l+r)/2-st]+st;
        if(v>l){
            rec(v,r);
        }
        v=dpr[(l+r+1)/2-st]+st;
        if(v<r){
            rec(l,v);
        }
    };
    rec(st,ed);
    cout << cnt << "\n";
}

signed main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}