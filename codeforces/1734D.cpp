#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct segtree{
    const int n;
    vector<ll> t;
    segtree(int n):n(n),t(4*n,-1e18){}
    void update(int l,int r,int i,int x,ll v){
        if(r<x||x<l)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,ll v){
        update(1,n,1,x,v);
    }
    ll query(int l,int r,int i,int x,int y){
        if(r<x||y<l)return -1e18;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
};

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<ll> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<ll> sl(n+2),sr(n+2);
    for(int i=k-1;i>=1;i--)sl[i]=a[i]+sl[i+1];
    for(int i=k+1;i<=n;i++)sr[i]=a[i]+sr[i-1];
    auto ml=sl,mr=sr;
    for(int i=k-1;i>=0;i--)ml[i]=min(sl[i],ml[i+1]);
    for(int i=k+1;i<=n+1;i++)mr[i]=min(sr[i],mr[i-1]);
    ll h=a[k],hl=a[k],hr=a[k];
    int l=k,r=k;
    ll lmx=0,rmx=-1e18;
    while(h>=0&&l>0&&r<=n){
        int nl=l,nr=r,li=-1,ri=-1;
        while(nl>0&&hr+ml[nl-1]>=0){
            nl--;
            if(sl[nl]-hl+a[k]>=lmx){
                lmx=sl[nl];
                li=nl;
            }
        }
        if(nl<1)break;
        while(nr<=n&&hl+mr[nr+1]>=0){
            nr++;
            if(sr[nr]-hr+a[k]>=rmx){
                rmx=sr[nr];
                ri=nr;
            }
        }
        if(nr>n)break;
        if(li==-1&&ri==-1){
            h=-1;
            break;
        }
        if(lmx>rmx){
            l=nl;
            hl+=lmx;
        }else{
            r=ri;
            hr+=rmx;
        }
        h=hl+hr+a[k];
    }
    if(h<0)cout << "NO\n";
    else cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}