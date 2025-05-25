#include<bits/stdc++.h>

using namespace std;

const int N=1000005;
const int K=1<<21;

int n,q;
int a[N],c[N];
vector<int> pos[N];
vector<pair<int,int>> upd[N],qr[N];
int ans[N];

struct Segtree{
    int t[K];
    void update(int l,int r,int i,int x,int v){
        if(l==r)return void(t[i]=max(t[i],v));
        int m=(l+r)/2;
        if(x<=m)update(l,m,i*2,x,v);
        else update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){update(1,n,1,x,v);}
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){return query(1,n,1,x,y);}
}seg;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    void update(int l,int r,int v){update(l,v),update(r+1,-v);}
}fen;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pos[a[i]].emplace_back(i);
        c[a[i]]++;
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    for(int i=1;i<=n;i++){
        c[i]+=c[i-1];
        for(int j=1;j<pos[i].size();j++){
            int v=seg.query(pos[i][j-1],pos[i][j]);
            fen.update(v+1,i,1);
        }
        for(auto j:pos[i])seg.update(j,i);
        for(auto [l,j]:qr[i])ans[j]=c[i]-c[l-1]-fen.query(l);
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}