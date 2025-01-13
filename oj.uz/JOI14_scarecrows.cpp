#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;
const int INF=INT_MAX/2;

int n;
pair<int,int> a[N];
int vals[N];
long long ans=0;

struct SegTree{
    struct Node{
        int mn,mn2,cnt;
        Node(){}
        Node(int val):mn(val),mn2(INF),cnt(1){}
        Node(int _mn,int _mn2,int _cnt):mn(_mn),mn2(_mn2),cnt(_cnt){}
        friend Node operator+(const Node &l,const Node &r){
            if(l.mn<r.mn)return Node(l.mn,min(l.mn2,r.mn),l.cnt);
            if(r.mn<l.mn)return Node(r.mn,min(r.mn2,l.mn),r.cnt);
            return Node(l.mn,min(l.mn2,r.mn2),l.cnt+r.cnt);
        }
    }t[K];
    int lz[K];
    void apply(int i,int v){
        if(t[i].mn>=v)return;
        t[i].mn=v;
        lz[i]=max(lz[i],v);
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void build(int l,int r,int i){
        lz[i]=0;
        if(l==r)return void(t[i]=Node(INF));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    int update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x||v<=t[i].mn)return 0;
        if(x<=l&&r<=y&&v<t[i].mn2)return apply(i,v),t[i].cnt;
        int m=(l+r)/2;
        push(i);
        int res=update(l,m,i*2,x,y,v)+update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
        return res;
    }
    int update(int x,int y,int v){
        return update(1,n,1,x,y,v);
    }
    void modify(int l,int r,int i,int x,int v){
        if(l==r)return void(t[i]=Node(v));
        int m=(l+r)/2;
        push(i);
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,int v){
        modify(1,n,1,x,v);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i].first >> a[i].second;
        a[i].first++,a[i].second++;
        vals[i]=a[i].second;
    }
    sort(a+1,a+n+1,greater<pair<int,int>>());
    sort(vals+1,vals+n+1);
    seg.build();
    for(int i=1;i<=n;i++){
        int id=lower_bound(vals+1,vals+n+1,a[i].second)-vals;
        ans+=seg.update(id+1,n,id);
        seg.modify(id,0);
    }
    cout << ans;
}