#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;;

int n,q;
int a[N];

struct segtree{
    array<int,10> t[K],lz[K];
    void pushlz(int l,int r,int i){
        for(int j=0;j<10;j++)t[i][j]+=lz[i][j];
        if(l<r){
            for(int j=0;j<10;j++){
                lz[i*2][j]+=lz[i][j];
                lz[i*2+1][j]+=lz[i][j];
            }
        }
        for(int j=0;j<10;j++)lz[i][j]=0;
    }
    void build(int l,int r,int i){
        if(l==r){
            for(int j=0;j<10;j++)t[i][j]=-1e9;
            t[i][l%10]=a[l];
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        for(int j=0;j<10;j++)t[i][j]=max(t[i*2][j],t[i*2+1][j]);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,int v,bool p){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            for(int j=0;j<10;j++)lz[i][j]=((l-l%10+j-v+10)%10)*(p?1:-1);
            pushlz(l,r,i);
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v,p);
        update(m+1,r,i*2+1,x,y,v,p);
        for(int j=0;j<10;j++)t[i][j]=max(t[i*2][j],t[i*2+1][j]);
    }
    void update(int x,int y,int v,bool p){
        update(1,n,1,x,y,v,p);
    }
    array<int,10> query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x){
            array<int,10> res;
            for(auto &x:res)x=-1e9;
            return res;
        }
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        auto ql=query(l,m,i*2,x,y);
        auto qr=query(m+1,r,i*2+1,x,y);
        array<int,10> res;
        for(int j=0;j<10;j++)res[j]=max(ql[j],qr[j]);
        return res;
    }
    int query(int x,int y){
        auto res=query(1,n,1,x,y);
        int mx=-1e9;
        for(auto x:res)mx=max(mx,x);
        return mx;
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    s.build();
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        l++,r++;
        if(t==1){
            s.update(l,r,l,0);
        }else if(t==2){
            s.update(l,r,l,1);
        }else{
            cout << s.query(l,r) << "\n";
        }
    }
}