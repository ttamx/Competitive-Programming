#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;
const int INF=1e9+7;

int n,q;
int h[N],a[N],b[N];
int ql[N],qr[N],ans[N];
vector<int> qrs[N],add[N],del[N];

struct Segtree{
    struct Node{
        int mx,mn,ans;
        Node():mx(-INF),mn(INF),ans(-1){}
        Node(int h):mx(h),mn(h),ans(-1){}
        friend Node operator+(const Node &lhs,const Node &rhs){
           Node res;
           res.mx=max(lhs.mx,rhs.mx);
           res.mn=min(lhs.mn,rhs.mn);
           res.ans=max(lhs.ans,rhs.ans);
           return res;
        }
    }t[K];
    struct Tag{
        int mx,mn;
        Tag():mx(-INF),mn(INF){}
        Tag(int h):mx(h),mn(h){}
        Tag &operator+=(const Tag &rhs){
            mx=max(mx,rhs.mx);
            mn=min(mn,rhs.mn);
            return *this;
        }
    }lz[K];
    void push(int l,int r,int i){
        t[i].ans=max(t[i].ans,lz[i].mx-t[i].mn);
        t[i].ans=max(t[i].ans,t[i].mx-lz[i].mn);
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=Tag();
    }
    void update(int l,int r,int i,int x,int y,int v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    void modify(int l,int r,int i,int x,int v){
        push(l,r,i);
        if(x<l||r<x)return;
        if(l==r){
            t[i].mn=v?h[l]:INF;
            t[i].mx=v?h[l]:-INF;
            return;
        }
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,int v){
        modify(1,n,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return -1;
        if(x<=l&&r<=y)return t[i].ans;
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> h[i] >> a[i] >> b[i];
        int l=i+a[i],r=i+b[i];
        if(l<=n)add[l].emplace_back(i);
        if(r<=n)del[r].emplace_back(i);
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> ql[i] >> qr[i];
        qrs[qr[i]].emplace_back(i);
    }
    for(int i=1;i<=n;i++){
        for(auto j:add[i])s.modify(j,1);
        s.update(i-b[i],i-a[i],h[i]);
        for(auto j:qrs[i])ans[j]=s.query(ql[j],qr[j]);
        for(auto j:del[i])s.modify(j,0);
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}