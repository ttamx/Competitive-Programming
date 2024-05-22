#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;
const int K=1<<20;
const ll INF=1e18;

int n,q;
ll d;
ll c[N];
vector<pair<int,int>> qr[N];
ll ans[N];
stack<pair<int,int>> st;

struct Segtree{
    struct node{
        ll ans,mn,mx;
        node():ans(0),mn(INF),mx(-INF){}
        node(ll v):ans(0),mn(v),mx(v){}
        node(ll _ans,ll _mn,ll _mx):ans(_ans),mn(_mn),mx(_mx){}
        friend node operator+(const node &lhs,const node &rhs){
            return node(lhs.ans+rhs.ans,min(lhs.mn,rhs.mn),max(lhs.mx,rhs.mx));
        }
    }t[K];
    ll lz[K];
    void pushlz(int l,int r,int i){
        t[i].ans+=(r-l+1)*lz[i];
        t[i].mn-=lz[i]*d;
        t[i].mx-=lz[i]*d;
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=node(c[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
    node query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    node query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> d;
    for(int i=1;i<=n;i++)cin >> c[i];
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    s.build();
    for(int r=1;r<=n;r++){
        int p=r;
        ll val=c[r];
        while(!st.empty()){
            auto [x,y]=st.top();
            auto res=s.query(x,y);
            ll dif=res.mx-val;
            if(dif<=0)break;
            ll t=(dif-1)/d+1;
            s.update(x,y,t);
            p=x;
            val=res.mn-t*d;
            st.pop();
        }
        st.emplace(p,r);
        for(auto [l,i]:qr[r]){
            auto res=s.query(l,r);
            ans[i]=res.mn<0?-1:res.ans;
        }
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}