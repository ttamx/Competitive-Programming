#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int N=2e5+5;
const ll inf=1e18;

struct LiChaoTree{
	struct node{
		ll m,c;
		node *l,*r;
		node(ll m=0,ll c=-inf):m(m),c(c),l(nullptr),r(nullptr){}
		ll get(ll x){
			return m*x+c;
		}
	};
	typedef node* pnode;
	pnode rt=nullptr;
	void update(ll l,ll r,pnode &t,ll m,ll c){
		if(!t)t=new node();
		node x(m,c);
		ll mid=(l+r)/2;
		if(x.get(mid)>t->get(mid))swap(x,*t);
		if(l==r)return;
		if(t->get(l)<x.get(l))update(l,mid,t->l,x.m,x.c);
		if(t->get(r)<x.get(r))update(mid+1,r,t->r,x.m,x.c);
	}
	void add(ll m,ll c){
		update(-inf,inf,rt,m,c);
	}
	ll query(ll l,ll r,pnode &t,ll x){
		if(!t||x<l||r<x)return -inf;
		if(l==r)return t->get(x);
		ll mid=(l+r)/2;
		return max({t->get(x),query(l,mid,t->l,x),query(mid+1,r,t->r,x)});
	}
	ll get(ll x){
		return query(-inf,inf,rt,x);
	}
}lct;

int n;
ll a[N],dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)dp[i]=dp[i-1]+a[i];
    ll ans=0;
    for(int i=n;i>=1;i--){
        ans=max(ans,lct.get(i)+dp[i-1]);;
        lct.add(-a[i],a[i]*i-dp[i-1]);
    }
    cout << ans;
}