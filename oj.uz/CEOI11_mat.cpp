#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int K=1<<21;
const int MOD=1e9+7;
const int BASE=1e6+3;

int n,m;
int a[N],b[N],c[N],pw[N];

void read(int n,int* a){
    for(int i=1;i<=n;i++){
        cin >> a[i];
        c[i]=a[i];
    }
    sort(c+1,c+n+1);
    for(int i=1;i<=n;i++)a[i]=lower_bound(c+1,c+n+1,a[i])-c;
}

struct Info{
    int val,base;
    Info():val(0),base(0){}
    Info(int val,int base):val(val),base(base){}
    friend Info operator+(const Info &l,const Info &r){
        return Info((l.val+r.val)%MOD,(l.base+r.base)%MOD);
    }
};

struct Segtree{
    Info t[K];
    int lz[K];
    void apply(int i,int v){
        t[i].val=(t[i].val+1LL*v*t[i].base)%MOD;
        lz[i]=(lz[i]+v)%MOD;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    void modify(int l,int r,int i,int x,Info v){
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        push(i);
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,Info v){
        modify(1,n,1,x,v);
    }
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
}fw;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    read(m,b);
    read(n,a);
    for(int i=1;i<=n;i++)c[b[i]]=i;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=1LL*pw[i-1]*BASE%MOD;
    int val=0;
    for(int i=1;i<=m;i++)val=(val+1LL*pw[i]*c[i])%MOD;
    vector<int> ans;
    for(int i=1;i<=n;i++){
        if(i>m){
            fw.update(a[i-m],-1);
            seg.update(a[i-m],n,MOD-1);
            seg.modify(a[i-m],Info());
        }
        fw.update(a[i],+1);
        seg.update(a[i],n,+1);
        seg.modify(a[i],Info(1LL*fw.query(a[i])*pw[i]%MOD,pw[i]));
        if(i>=m&&seg.t[1].val==1LL*val*pw[i-m]%MOD){
            ans.emplace_back(i-m+1);
        }
    }
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}