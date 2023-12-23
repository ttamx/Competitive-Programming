#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int K=1<<21;

int n,q;

struct segtree{
    struct node{
        int good,bad;
        node():good(0),bad(0){}
        node(int good,int bad):good(good),bad(bad){}
        int sum(){
            return good+bad;
        }
        friend node operator+(node lhs,node rhs){
            return node(lhs.good+rhs.good,lhs.bad+rhs.bad);
        }
    }t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=node(1,0));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(0,n,1);
    }
    void add(int l,int r,int i,int v){
        if(l==r)return void(t[i].bad++);
        int m=(l+r)/2;
        int freq=t[i*2].sum();
        if(freq>=v)add(l,m,i*2,v);
        else add(m+1,r,i*2+1,v-freq);
        t[i]=t[i*2]+t[i*2+1];
    }
    void add(int v){
        add(0,n,1,v);
    }
    void del(int l,int r,int i,int v){
        if(l==r){
            if(v==t[i].good)t[i].good--;
            else t[i].bad--;
            return;
        }
        int m=(l+r)/2;
        int freq=t[i*2].sum();
        if(freq>=v)del(l,m,i*2,v);
        else del(m+1,r,i*2+1,v-freq);
        t[i]=t[i*2]+t[i*2+1];
    }
    void del(int v){
        del(0,n,1,v);
    }
    node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    node query(int x,int y){
        return query(0,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    s.build();
    s.del(0);
    while(q--){
        char o;
        cin >> o;
        if(o=='d'){
            int x;
            cin >> x;
            s.del(x+1);
        }else if(o=='g'){
            int x;
            cin >> x;
            s.add(x+1);
        }else{
            int x,y;
            cin >> x >> y;
            auto res=s.query(x,y-1);
            cout << y-x+res.bad-res.good << "\n";
        }
    }
}