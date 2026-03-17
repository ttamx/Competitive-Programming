#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int K=1<<21;

string s;
int n;
int a[N];

struct Segtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=a[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return INT_MAX;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> s;
    n=s.size();
    for(int i=0;i<n;i++){
        a[i+1]=a[i]+(s[i]=='('?+1:-1);
    }
    seg.build(0,n,1);
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        int mn=seg.query(0,n,1,l-1,r);
        int rem=a[l-1]-mn;
        int bal=a[r]-a[l-1]+rem;
        cout << r-l+1-rem-bal << "\n";
    }
}