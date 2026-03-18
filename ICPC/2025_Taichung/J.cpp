#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int K=1<<20;
const int INF=1e9;

int n;
int a[N],h[N];
vector<tuple<int,int,int>> upd[N];
int ans[N];

struct Segtree{
    struct Node{
        int mn,mn2,cnt;
        friend Node operator+(Node l,Node r){
            if(l.mn<r.mn)return Node{l.mn,min(l.mn2,r.mn),l.cnt};
            if(l.mn>r.mn)return Node{r.mn,min(r.mn2,l.mn),r.cnt};
            return Node{l.mn,min(l.mn2,r.mn2),l.cnt+r.cnt};
        }
    }t[K];
    int lz[K];
    void apply(int i,int v){
        t[i].mn+=v;
        t[i].mn2+=v;
        lz[i]+=v;
    }
    void chmax(int i,int v){
        t[i].mn=max(t[i].mn,v);
    }
    void push(int i){
        apply(i*2,lz[i]);
        chmax(i*2,t[i].mn);
        apply(i*2+1,lz[i]);
        chmax(i*2+1,t[i].mn);
        lz[i]=0;
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Node{0,INF,1});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
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
    void work(int l,int r,int i){
        if(t[i].mn>0)return;
        if(t[i].mn2>0)return chmax(i,0);
        push(i);
        int m=(l+r)/2;
        work(l,m,i*2);
        work(m+1,r,i*2+1);
        pull(i);
    }
}seg;

struct Info{
    int idx,h,lz;
    void apply(int hh,int v){
        assert(h>hh);
        upd[idx].emplace_back(hh+1,h,v);
        lz+=v;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<n;i++){
        cin >> h[i];
    }
    h[n]=n+1;
    vector<Info> st;
    for(int i=n;i>=1;i--){
        while(!st.empty()&&st.back().h<=h[i]){
            auto e=st.back();
            st.pop_back();
            if(!st.empty()){
                st.back().apply(e.h,e.lz);
            }
        }
        if(h[i]>0){
            st.emplace_back(Info{i,h[i],0});
        }
        if(a[i]==0)continue;
        int l=-1,r=st.size()-1;
        while(l<r){
            int m=(l+r+1)/2;
            if(st[m].h>a[i])l=m;
            else r=m-1;
        }
        assert(l!=-1);
        int p=l;
        int hh=0;
        if(p<st.size()-1){
            st.back().apply(0,+1);
            st[p+1].lz--;
            hh=st[p+1].h;
        }
        upd[st[p].idx].emplace_back(hh+1,a[i],+1);
    }
    while(!st.empty()){
        auto e=st.back();
        st.pop_back();
        if(!st.empty()){
            st.back().apply(e.h,e.lz);
        }
    }
    seg.build(1,n,1);
    for(int i=n;i>=1;i--){
        for(auto [l,r,v]:upd[i]){
            seg.update(1,n,1,l,r,v);
        }
        auto tmp=seg.t[1];
        ans[i]=n-(tmp.mn==0?tmp.cnt:0);
        seg.apply(1,-1);
        seg.work(1,n,1);
    }
    for(int i=1;i<=n;i++){
        cout << ans[i] << " \n"[i==n];
    }
}