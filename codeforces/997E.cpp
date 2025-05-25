#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=120005;
const int K=1<<18;
const int INF=INT_MAX/2;

int n,q;
int a[N],pos[N];
vector<pair<int,int>> qr[N];
ll ans[N];

struct SegTree{
    struct Info{
        int mn,cnt;
        ll ans;
        friend Info operator+(const Info &l,const Info &r){
            if(l.mn<r.mn)return Info{l.mn,l.cnt,l.ans+r.ans};
            if(r.mn<l.mn)return Info{r.mn,r.cnt,l.ans+r.ans};
            return Info{l.mn,l.cnt+r.cnt,l.ans+r.ans};
        }
    }t[K];
    int lz1[K],lz2[K];
    void apply1(int i,int v){t[i].mn+=v,lz1[i]+=v;}
    void apply2(int i,int v){t[i].ans+=1LL*t[i].cnt*v,lz2[i]+=v;}
    void push(int i){
        apply1(i*2,lz1[i]);
        apply1(i*2+1,lz1[i]);
        if(t[i].mn==t[i*2].mn)apply2(i*2,lz2[i]);
        if(t[i].mn==t[i*2+1].mn)apply2(i*2+1,lz2[i]);
        lz1[i]=lz2[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Info{0,1,0});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){build(1,n,1);}
    void update1(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply1(i,v);
        int m=(l+r)/2;
        push(i);
        update1(l,m,i*2,x,y,v);
        update1(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update1(int x,int y,int v){update1(1,n,1,x,y,v);}
    void update2(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x||t[i].mn>1)return;
        if(x<=l&&r<=y)return apply2(i,v);
        int m=(l+r)/2;
        push(i);
        update2(l,m,i*2,x,y,v);
        update2(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update2(int x,int y,int v){update2(1,n,1,x,y,v);}
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i].ans;
        int m=(l+r)/2;
        push(i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){return query(1,n,1,x,y);}
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pos[a[i]]=i;
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    seg.build();
    for(int i=1;i<=n;i++){
        seg.update1(1,i,+1);
        if(a[i]>1&&pos[a[i]-1]<i)seg.update1(1,pos[a[i]-1],-1);
        if(a[i]<n&&pos[a[i]+1]<i)seg.update1(1,pos[a[i]+1],-1);
        seg.update2(1,i,+1);
        for(auto [l,j]:qr[i])ans[j]=seg.query(l,i);
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}