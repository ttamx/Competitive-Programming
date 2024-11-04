#include<bits/stdc++.h>

using namespace std;

const int K=1<<18;
const int MOD=123456789;

int n,q;

struct SegTree{
    int t[K];
    void modify(int l,int r,int i,int x,int v){
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        t[i]=1LL*t[i*2]*t[i*2+1]%MOD;
    }
    void modify(int x,int v){
        modify(1,n,1,x,v);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        seg.modify(i,(x+MOD+1)%MOD);
    }
    cout << (seg.t[1]+MOD-1)%MOD << "\n";
    while(q--){
        int i,x;
        cin >> i >> x;
        seg.modify(i,(x+MOD+1)%MOD);
        cout << (seg.t[1]+MOD-1)%MOD << "\n";
    }
}