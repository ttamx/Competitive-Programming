#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1<<18;

int n,q;
int a[N];

struct Segtree{
    int t[N*2];
    int build(int l,int r,int i){
        if(l==r)return t[i]=a[l],0;
        int m=(l+r)/2;
        build(l,m,i*2);
        int s=build(m+1,r,i*2+1);
        if(s)t[i]=t[i*2]^t[i*2+1];
        else t[i]=t[i*2]|t[i*2+1];
        return s^1;
    }
    int update(int l,int r,int i,int x,int v){
        if(l==r)return t[i]=v,0;
        int m=(l+r)/2;
        int s;
        if(x<=m)s=update(l,m,i*2,x,v);
        else s=update(m+1,r,i*2+1,x,v);
        if(s)t[i]=t[i*2]^t[i*2+1];
        else t[i]=t[i*2]|t[i*2+1];
        return s^1;
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    n=1<<n;
    for(int i=1;i<=n;i++)cin >> a[i];
    seg.build(1,n,1);
    while(q--){
        int x,v;
        cin >> x >> v;
        seg.update(1,n,1,x,v);
        cout << seg.t[1] << "\n";
    }
}