#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const ll INF=LLONG_MAX/2;

int n,m;
int v[N],c[N],pos[N];
ll ans=-INF;
pair<int,int> a[N];
vector<pair<int,int>> vec;

struct Persist{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll val;
        int freq;
        Ptr l,r;
        Node(ll val,int freq):val(val),freq(freq),l(nullptr),r(nullptr){}
    };
    Ptr rt[N];
    void build(int l,int r,Ptr &t){
        t=new Node(0,0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int t){
        build(1,n,rt[t]);
    }
    void update(int l,int r,Ptr &t,Ptr k,int x,ll v){
        t=new Node(*k);
        t->val+=v;
        t->freq++;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,k->l,x,v);
        else update(m+1,r,t->r,k->r,x,v);
    }
    void update(int k,int t,int x,ll v){
        update(1,n,rt[t],rt[k],x,v);
    }
    ll query(int l,int r,Ptr tl,Ptr tr,int k){
        if(l==r)return tr->val-tl->val;
        int m=(l+r)/2;
        int freq=tr->r->freq-tl->r->freq;
        if(freq<k)return query(l,m,tl->l,tr->l,k-freq)+tr->r->val-tl->r->val;
        return query(m+1,r,tl->r,tr->r,k);
    }
    ll query(int l,int r,int k){
        return query(1,n,rt[l-1],rt[r],k);
    }
}s;

void dnc(int l,int r,int optl,int optr){
    if(l>r)return;
    int mid=(l+r)/2;
    ll res=-INF;
    int opt=-1;
    int p=max(optl,mid+m-1);
    for(int i=p;i<=optr;i++){
        ll tmp=s.query(mid,i,m)-2*c[i];
        if(tmp>res)res=tmp,opt=i;
    }
    res+=2*c[mid];
    ans=max(ans,res);
    dnc(l,mid-1,optl,opt);
    dnc(mid+1,r,opt,optr);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i].second >> a[i].first;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        tie(c[i],v[i])=a[i];
        vec.emplace_back(v[i],i);
    }
    sort(vec.begin(),vec.end());
    for(int i=0;i<n;i++)pos[vec[i].second]=i+1;
    s.build(0);
    for(int i=1;i<=n;i++)s.update(i-1,i,pos[i],v[i]);
    dnc(1,n-m+1,1,n);
    cout << ans;
}