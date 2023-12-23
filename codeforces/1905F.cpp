#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int K=1<<20;

struct segtree{
	struct node{
		int val,freq;
		node():val(INF),freq(0){}
		node(int val,int freq=1):val(val),freq(freq){}
		friend node operator+(node a,node b){
			if(a.val<b.val)return a;
			if(b.val<a.val)return b;
			return node(a.val,a.freq+b.freq);
		}
	}t[K];
	int lz[K];
	void pushlz(int l,int r,int i){
		t[i].val+=lz[i];
		if(l<r){
			lz[i*2]+=lz[i];
			lz[i*2+1]+=lz[i];
		}
		lz[i]=0;
	}
	void build(int l,int r,int i){
        lz[i]=0;
		if(l==r)return void(t[i]=node(2,1));
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]+t[i*2+1];
	}
	void update(int l,int r,int i,int x,int y,int v){
		pushlz(l,r,i);
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i);
		int m=(l+r)/2;
		update(l,m,i*2,x,y,v);
		update(m+1,r,i*2+1,x,y,v);
		t[i]=t[i*2]+t[i*2+1];
	}
	int query(int l,int r,int i,int x){
		pushlz(l,r,i);
		if(l==r)return t[i].val;
		int m=(l+r)/2;
		if(x<=m)return query(l,m,i*2,x);
		return query(m+1,r,i*2+1,x);
	}
}s;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2),b(n+2);
    bool sorted=true;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[a[i]]=i;
        sorted&=a[i]==i;
    }
    if(sorted)return void(cout << n-2 << "\n");
    b[n+1]=INF;
    auto calc=[&](int i){
        return (b[i-1]<b[i]?-1:1)+(b[i+1]<b[i]?-1:1);
    };
    s.build(1,n,1);
    for(int i=1;i<=n;i++)s.update(1,n,1,i,n,calc(a[i]));
    for(int i=1;i<=n;i++)if(i!=a[i])s.update(1,n,1,i,i,1);
    auto get=[&](){
        return s.t[1].val==2?s.t[1].freq:0;
    };
    int ans=get();
    auto valid=[&](int i){
        return 1<=i&&i<=n;
    };
    auto upd=[&](int x,int y){
        set<int> p;
        for(int i=-1;i<=1;i++){
            if(valid(a[x]+i))p.emplace(a[x]+i);
            if(valid(a[y]+i))p.emplace(a[y]+i);
        }
        for(auto i:p)s.update(1,n,1,b[i],n,-calc(i));
        if(x!=a[x])s.update(1,n,1,x,x,-1);
        if(y!=a[y])s.update(1,n,1,y,y,-1);
        swap(b[a[x]],b[a[y]]);
        swap(a[x],a[y]);
        for(auto i:p)s.update(1,n,1,b[i],n,calc(i));
        if(x!=a[x])s.update(1,n,1,x,x,1);
        if(y!=a[y])s.update(1,n,1,y,y,1);
        ans=max(ans,get());
    };
    vector<pii> pre(n+2),suf(n+2);
    suf[n+1]=pii(INF,n+1);
    for(int i=1;i<=n;i++)pre[i]=max(pre[i-1],pii(a[i],i));
    for(int i=n;i>=1;i--)suf[i]=min(suf[i+1],pii(a[i],i));
    for(int i=1;i<=n;i++){
        if(a[i]==i){
            int l=pre[i-1].second,r=suf[i+1].second;
            if(l<1||r>n)continue;
            upd(l,r);
            upd(l,r);
        }else{
            int l=b[i],r=i;
            upd(l,r);
            upd(l,r);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}