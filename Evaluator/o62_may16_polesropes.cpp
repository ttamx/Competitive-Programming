#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,m;

struct segtree{
    int t[K],lz[K];
    bool islz[K];
    void pushlz(int l,int r,int i){
        if(!islz[i])return;
        islz[i]=false;
        t[i]=lz[i]*(r-l+1);
        if(l<r){
            lz[i*2]=lz[i*2+1]=lz[i];
            islz[i*2]=islz[i*2+1]=true;
        }
    }
    void setval(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            islz[i]=true;
            lz[i]=v;
            pushlz(l,r,i);
            return;
        }
        int m=(l+r)/2;
        setval(l,m,i*2,x,y,v);
        setval(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void setval(int x,int y,int v){
        setval(0,n,1,x,y,v);
    }
    void addval(int l,int r,int i,int x,int v){
        pushlz(l,r,i);
        if(x<l||r<x)return;
        if(l==r)return void(t[i]+=v);
        int m=(l+r)/2;
        addval(l,m,i*2,x,v);
        addval(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void addval(int x,int v){
        addval(0,n,1,x,v);
    }
    int rbsearch(int l,int r,int i,int v){
        if(l==r)return l;
        int m=(l+r)/2;
        pushlz(l,m,i*2);
        pushlz(m+1,r,i*2+1);
        if(t[i*2]>=v)return rbsearch(l,m,i*2,v);
        else return rbsearch(m+1,r,i*2+1,v-t[i*2]);
    }
    int rbsearch(int v){
        return rbsearch(0,n,1,v);
    }
    int lbsearch(int l,int r,int i,int v){
        if(l==r)return l;
        int m=(l+r)/2;
        pushlz(l,m,i*2);
        pushlz(m+1,r,i*2+1);
        if(t[i*2+1]<v)return lbsearch(l,m,i*2,v-t[i*2+1]);
        else return lbsearch(m+1,r,i*2+1,v);
    }
    int lbsearch(int v){
        return lbsearch(0,n,1,v);
    }
    int query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    int query(int x,int y){
        return query(0,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    s.setval(1,n-1,10);
    while(m--){
        int t;
        cin >> t;
        if(t==1){
            int x,y;
            cin >> x >> y;
            int l=min(y/2,s.query(0,x-1)),r=min(y/2,s.query(x+1,n));
            if(l<y/2)r=y-l;
            if(r<y/2)l=y-r;
            int li=s.lbsearch(l+s.query(x,n)),ri=s.rbsearch(r+s.query(0,x));
            l-=s.query(li+1,x-1);
            r-=s.query(x+1,ri-1);
            s.setval(li+1,x-1,0);
            s.setval(x+1,ri-1,0);
            s.addval(li,-l);
            s.addval(ri,-r);
            s.addval(x,y);
        }else{
            int x;
            cin >> x;
            cout << s.query(x,x) << "\n";
        }
    }
}