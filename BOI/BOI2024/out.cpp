
#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long
#define int long long
 
const int nx=2e5+5;
 
ll n, m, cnt, ans;
map<ll, ll> mp;
vector<pair<ll, ll>> v;
 
struct cake
{
    ll v, c, idx;
    cake(): v(0), c(0), idx(0){}
    bool operator< (const  cake &o) const {return c<o.c;}
} c[nx];
 
struct persist
{
    struct node
    {
        ll f, s;
        node *l, *r;
        node(ll f, ll s): f(f), s(s){}
    };
    typedef node* pnode;
    pnode rt[nx];
    void build(int l, int r, pnode &k)
    {
        k=new node(0, 0);
        if (l==r) return;
        int md=(l+r)/2;
        build(l, md, k->l);
        build(md+1, r, k->r);
    }
    void update(int l, int r, pnode &k, pnode t, int idx, ll vl)
    {
        k=new node(*t);
        k->f++;
        k->s+=vl;
        if (l==r) return;
        int md=(l+r)/2;
        if (idx<=md) update(l, md, k->l, t->l, idx, vl);
        else update(md+1, r, k->r, t->r, idx, vl);
    }
    ll query2(int l, int r, pnode k, pnode t, ll key)
    {
        if (l==r) return k->s-t->s;
        int md=(l+r)/2;
        if (k->r->f-t->r->f<key) return query2(l, md, k->l, t->l, key-(k->r->f-t->r->f))+k->r->s-t->r->s;
        else return query2(md+1, r, k->r, t->r, key);
    }
    ll query(int l, int r)
    {
        return query2(1, n, rt[r], rt[l-1], m)-2*(c[r].c-c[l].c);
    }
} s;
 
void solve(int l, int r, int optl, int optr)
{
    if (r<l) return;
    int md=(l+r)/2;
    pair<ll, ll> mx={-1e18, 0};
    for (int i=optl; i<=min(md-m+1, (ll)optr); i++) mx=max(mx, {s.query(i, md), i});
    ans=max(ans, mx.first);
    solve(l, md-1, optl, mx.second);
    solve(md+1, r, mx.second, optr);
}
 
int32_t main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    cin>>n>>m;
    for (int i=1; i<=n; i++) cin>>c[i].v>>c[i].c, v.push_back({c[i].v, i});
    sort(v.begin(), v.end());
    for (int i=0; i<n; i++) c[v[i].second].idx=i+1;
    sort(c+1, c+n+1);
    s.build(1, n, s.rt[0]);
    for (int i=1; i<=n; i++) s.update(1, n, s.rt[i], s.rt[i-1], c[i].idx, c[i].v);
    //for (int i=1; i<=n; i++) for (int j=i; j<=n; j++) cout<<"debug "<<i<<' '<<j<<' '<<s.query(i, j)<<'\n';
    solve(m, n, 1, n);
    cout<<ans;
}
 
/*
2 2
1 1
1 1
*/