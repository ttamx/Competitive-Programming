#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

int n,m;
int a[N];

struct Segtree{
    struct Node{
        int ans,pre,suf,sum;
        Node(){
            ans=pre=suf=sum=0;
        }
        Node(int val){
            ans=pre=suf=max(val,0);
            sum=val;
        }
        friend Node operator+(Node l,Node r){
            Node res;
            res.ans=max({l.ans,r.ans,l.suf+r.pre});
            res.pre=max(l.pre,l.sum+r.pre);
            res.suf=max(l.suf+r.sum,r.suf);
            res.sum=l.sum+r.sum;
            return res;
        }
    }t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Node(a[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    Node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i];
    s.build(1,n,1);
    while(m--){
        int l,r;
        cin >> l >> r;
        l++,r++;
        cout << s.query(1,n,1,l,r).ans << "\n";
    }
}