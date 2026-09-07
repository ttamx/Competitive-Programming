#include<bits/stdc++.h>

using namespace std;

using ll = long long;

using T = array<ll,4>;

struct Node;
using Ptr = Node*;
struct Node{
    int cnt;
    ll sum;
    Ptr l,r;
    Node():cnt(0),sum(0),l(),r(){}
};

void build(int l,int r,Ptr &t){
    t=new Node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}
void update(int l,int r,Ptr &t,Ptr o,int x,ll v){
    t=new Node(*o);
    t->cnt++;
    t->sum+=v;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,o->l,x,v);
    else update(m+1,r,t->r,o->r,x,v);
}
ll query(int l,int r,Ptr tl,Ptr tr,int k){
    if(l==r)return tr->sum-tl->sum;
    int m=(l+r)/2;
    int cnt=tr->l->cnt-tl->l->cnt;
    if(k<=cnt)return query(l,m,tl->l,tr->l,k);
    else return query(m+1,r,tl->r,tr->r,k-cnt)+tr->l->sum-tl->l->sum;
}
ll getkth(int l,int r,Ptr tl,Ptr tr,int k){;
    if(l==r)return tr->sum-tl->sum;
    int m=(l+r)/2;
    int cnt=tr->l->cnt-tl->l->cnt;
    if(k<=cnt)return getkth(l,m,tl->l,tr->l,k);
    else return getkth(m+1,r,tl->r,tr->r,k-cnt);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q,d;
    cin >> n >> q >> d;
    vector<ll> a(n+1),ord(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    for(int i=n;i>=d;i--)a[i]-=a[i-d];
    vector<pair<ll,int>> vals;
    for(int i=d;i<=n;i++)vals.emplace_back(a[i],i);
    sort(vals.rbegin(),vals.rend());
    int k=vals.size();
    for(int i=0;i<k;i++)ord[vals[i].second]=i;
    vector<Ptr> root(n+1);
    build(0,k-1,root[d-1]);
    for(int i=d;i<=n;i++)update(0,k-1,root[i],root[i-1],ord[i],a[i]);
    while(q--){
        int l,r,c,p;
        cin >> l >> r >> c >> p;
        l+=d-1;
        if(l>r){
            cout << 0 << "\n";
            continue;
        }
        int lo=0,hi=min(c,r-l+1);
        while(lo<hi){
            int m=(lo+hi+1)/2;
            if(getkth(0,k-1,root[l-1],root[r],m)>1LL*(2*m-1)*p)lo=m;
            else hi=m-1;
        }
        cout << (lo?query(0,k-1,root[l-1],root[r],lo)-1LL*lo*lo*p:0LL) << "\n";
    }
}