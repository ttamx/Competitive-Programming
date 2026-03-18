#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=2e5+5;

int n,q;
ll a[N];
int ord[N];
vector<pair<ll,int>> b;

struct Node;
using Ptr = Node*;
struct Node{
    ll sum;
    mint prod;
    Ptr l,r;
    Node(ll sum,mint prod):sum(sum),prod(prod),l(),r(){}
};

Ptr root[N];

void build(int l,int r,Ptr &t){
    t=new Node(0,1);
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void update(int l,int r,Ptr &t,Ptr o,int x,int v){
    t=new Node(*o);
    t->sum+=v-1;
    t->prod*=v;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,o->l,x,v);
    else update(m+1,r,t->r,t->r,x,v);
}

pair<ll,mint> query(int l,int r,Ptr tl,Ptr tr,ll k){
    if(l==r){
        ll sum=tr->sum-tl->sum;
        mint prod=tr->prod/tl->prod;
        if(sum<=k)return {sum,prod};
        return {0LL,mint(1)};
    }
    int m=(l+r)/2;
    ll sum=tr->r->sum-tl->r->sum;
    mint prod=tr->r->prod/tl->r->prod;
    if(sum>k){
        return query(m+1,r,tl->r,tr->r,k);
    }else{
        auto [s,p]=query(l,m,tl->l,tr->l,k-sum);
        return {sum+s,prod*p};
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b.emplace_back(a[i],i);
    }
    sort(b.begin(),b.end());
    for(int i=0;i<n;i++){
        ord[b[i].second]=i+1;
    }
    build(1,n,root[0]);
    for(int i=1;i<=n;i++){
        update(1,n,root[i],root[i-1],ord[i],a[i]);
    }
    for(int i=1;i<=n;i++){
        a[i]--;
        a[i]+=a[i-1];
    }
    while(q--){
        int l,r;
        ll k;
        cin >> l >> r >> k;
        k=(a[r]-a[l-1])-k;
        if(k<=0){
            cout << 1 << "\n";
            continue;
        }
        auto [sum,prod]=query(1,n,root[l-1],root[r],k);
        cout << prod*(1+k-sum) << "\n";
    }
}