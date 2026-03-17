#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;

int n,q;
int a[N],cnt[N];

struct Info{
    int mn,cnt;
    friend Info operator+(const Info &l,const Info &r){
        if(l.mn<r.mn)return l;
        if(l.mn>r.mn)return r;
        return Info{l.mn,l.cnt+r.cnt};
    }
};

struct Segtree{
    Info t[K];
    int lz[K];
    void apply(int i,int v){
        t[i].mn+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Info{0,1});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    seg.build();
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]=min(a[i],n+1);
        cnt[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(cnt[i]>0){
            seg.update(max(1,i-cnt[i]+1),i,+1);
        }
    }
    cin >> q;
    while(q--){
        int x,y;
        cin >> x >> y;
        int v=a[x];
        if(v<=n){
            seg.update(max(1,v-cnt[v]+1),v,-1);
        }
        cnt[v]--;
        if(v<=n&&cnt[v]>0){
            seg.update(max(1,v-cnt[v]+1),v,+1);
        }
        v=a[x]=min(y,n+1);
        if(v<=n&&cnt[v]>0){
            seg.update(max(1,v-cnt[v]+1),v,-1);
        }
        cnt[v]++;
        if(v<=n){
            seg.update(max(1,v-cnt[v]+1),v,+1);
        }
        cout << (seg.t[1].mn==0?seg.t[1].cnt:0) << "\n";
    }
}