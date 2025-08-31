#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;

int n,m;
int s[N],h[N],t[N];
pair<int,int> a[N];

struct Info{
    int val,idx;
    Info():val(0),idx(0){}
    Info(int _val,int _idx):val(_val),idx(_idx){}
    friend Info operator+(const Info &l,const Info &r){
        return l.val>r.val?l:r;
    }
};

struct Segtree{
    Info t[K];
    void modify(int l,int r,int i,int x,const Info &v){
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,const Info &v){
        modify(1,m,1,x,v);
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Info query(int x,int y){
        return query(1,m,1,x,y);
    }
}seg;

struct LazySegtree{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,m,1,x,y,v);
    }
    int findfirst(int l,int r,int i){
        if(l==r)return l;
        push(i);
        int m=(l+r)/2;
        if(t[i*2]<0)return findfirst(l,m,i*2);
        else return findfirst(m+1,r,i*2+1);
    }
    int findfirst(){
        return findfirst(1,m,1);
    }
}seg2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> s[i];
    }
    for(int i=1;i<=m;i++){
        cin >> h[i] >> t[i];
        a[i]={h[i],i};
    }
    sort(a+1,a+m+1);
    for(int i=1;i<=m;i++){
        h[a[i].second]=i;
    }
    for(int i=1;i<=n;i++){
        s[i]=lower_bound(a+1,a+m+1,make_pair(s[i],0))-a-1;
    }
    for(int i=1;i<=m;i++){
        seg.modify(h[i],Info(t[i],h[i]));
    }
    ll base=0;
    for(int i=1;i<=n;i++){
        if(s[i]==0){
            cout << base << " ";
            continue;
        }
        seg2.update(s[i],m,-1);
        int j=seg2.findfirst();
        auto res=seg.query(1,j);
        if(res.idx){
            base+=res.val;
            seg.modify(res.idx,Info());
            seg2.update(res.idx,m,+1);
        }else{
            seg2.update(s[i],m,+1);
        }
        cout << base << " ";
    }
    cout << "\n";
}