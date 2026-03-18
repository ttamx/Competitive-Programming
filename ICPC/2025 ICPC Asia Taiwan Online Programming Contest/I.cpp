#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;

int n,q;
ll a[N];
vector<pair<int,int>> upd[N];
vector<int> vent[N],hit[N];
int op[N],ql[N],qr[N],qk[N];

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(;i<N;i+=i&-i){
            t[i]+=v;
        }
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    int find(ll v){
        int x=0;
        for(int i=1<<17;i>0;i>>=1){
            if(x+i<N&&t[x+i]<v){
                v-=t[x+=i];
            }
        }
        return x+1;
    }
}f;

struct Info{
    ll sum,ans;
    Info():sum(0),ans(0){}
    Info(ll sum,ll ans):sum(sum),ans(ans){}
    friend Info operator+(const Info &l,const Info &r){
        return Info(l.sum+r.sum,l.ans+r.ans);
    }
};

struct Segtree{
    Info t[K];
    ll lz[K];
    void apply(int i,ll v){
        t[i].ans+=v*t[i].sum;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
    void update_single(int l,int r,int i,int x,ll v1,ll v2){
        if(x<l||r<x)return;
        if(l==r){
            t[i].sum+=v1;
            t[i].ans+=v2;
            return;
        }
        push(i);
        int m=(l+r)/2;
        update_single(l,m,i*2,x,v1,v2);
        update_single(m+1,r,i*2+1,x,v1,v2);
        pull(i);
    }
    void update_single(int x,ll v1,ll v2){
        update_single(1,n,1,x,v1,v2);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0LL;
        if(x<=l&&r<=y)return t[i].ans;
        push(i);
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=q;i++){
        cin >> op[i] >> ql[i] >> qr[i];
        if(op[i]==1){
            cin >> qk[i];
            upd[ql[i]].emplace_back(i,qk[i]);
            upd[qr[i]+1].emplace_back(i,-qk[i]);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto [j,v]:upd[i]){
            f.update(j,v);
        }
        ll lim=a[i];
        int cur=0;
        while(lim>1){
            cur=f.find(f.query(cur)+lim);
            if(cur>q)break;
            vent[cur].emplace_back(i);
            lim/=2;
        }
        if(lim==1&&cur<=q){
            hit[cur].emplace_back(i);
        }
    }
    for(auto j:hit[0]){
        seg.update_single(j,1,0);
    }
    for(int i=1;i<=q;i++){
        int l=ql[i],r=qr[i];
        for(auto j:vent[i]){
            seg.update_single(j,0,1);
        }
        if(op[i]==1){
            seg.update(l,r,1);
        }else{
            cout << seg.query(l,r) << "\n";
        }
        for(auto j:hit[i]){
            seg.update_single(j,1,0);
        }
    }
}