#include<bits/stdc++.h>
 
using namespace std;

const int N=5e5+5;
const int K=1<<20;
const int INF=INT_MAX/2;

int n,m,q;
vector<int> upd[N];
vector<pair<int,int>> qrs[N];
bool ans[N];

struct SegTree{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]=max(t[i],v);
        lz[i]=max(lz[i],v);
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
        update(1,n,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return INF;
        if(x<=l&&r<=y)return t[i];
        push(i);
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        upd[r].emplace_back(l);
    }
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        qrs[r].emplace_back(l,i);
    }
    for(int r=1;r<=n;r++){
        for(auto l:upd[r]){
            seg.update(l,r,l);
        }
        for(auto [l,i]:qrs[r]){
            ans[i]=(seg.query(l,r)>=l);
        }
    }
    for(int i=0;i<q;i++){
        cout << (ans[i]?"YES":"NO") << "\n";
    }
}