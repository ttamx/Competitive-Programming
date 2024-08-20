#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

const int N=100005;

int n,k,q;
ll a[N];
ll ans;

struct SegTree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll sum,cnt;
        Ptr l,r;
        Node():sum(0LL),cnt(0LL),l(),r(){}
        Node(ll _sum,ll _cnt):sum(_sum),cnt(_cnt),l(),r(){}
    };
    ll lb,ub;
    Ptr root;
    SegTree(ll _lb,ll _ub):lb(_lb),ub(_ub),root(new Node()){}
    void update(ll l,ll r,Ptr &t,ll x,ll v,ll c){
        if(!t)t=new Node();
        t->sum+=v;
        t->cnt+=c;
        if(l==r)return;
        ll m=l+(r-l)/2;
        if(x<=m)update(l,m,t->l,x,v,c);
        else update(m+1,r,t->r,x,v,c);
    }
    void update(ll x,ll v,ll c){
        update(lb,ub,root,x,v,c);
    }
    ll bsearch(ll l,ll r,Ptr &t,ll suml,ll cntr){
        if(l==r)return l;
        if(!t)t=new Node();
        ll m=l+(r-l)/2;
        ll sum=(t->l?t->l->sum:0LL);
        ll cnt=(t->r?t->r->cnt:0LL);
        if(suml+sum+(cntr+cnt)*i128(m)>=i128(m)*k){
            return bsearch(m+1,r,t->r,suml+sum,cntr);
        }else{
            return bsearch(l,m,t->l,suml,cntr+cnt);
        }
    }
    ll bsearch(){
        return bsearch(lb,ub,root,0LL,0LL);
    }
}seg(-1LL,ll(1e18));

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        seg.update(a[i],a[i],1);
    }
    cin >> q;
    for(int i=0;i<q;i++){
        int x,y;
        cin >> x >> y;
        x=(x^ans)%n+1;
        seg.update(a[x],-a[x],-1);
        a[x]+=y;
        seg.update(a[x],a[x],1);
        ans=seg.bsearch()-1;
        cout << ans << "\n";
    }
}