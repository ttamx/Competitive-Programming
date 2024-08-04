#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int N=1e5+5;

int n,q;
int a[N];

struct SegTree{
    struct Node{
        vector<ll> dat;
        bool ok;
        Node():dat(0),ok(false){}
    }t[4*N];
    Node merge(const Node &l,const Node &r){
        Node res;
        if(l.ok||r.ok){
            res.ok=true;
            return res;
        }
        int i=0,j=0,p=0;
        int id=-1;
        vector<bool> ok;
        while(i<l.dat.size()||j<r.dat.size()){
            if(j==r.dat.size()||(i<l.dat.size()&&l.dat[i]<r.dat[j])){
                res.dat.emplace_back(l.dat[i]);
                i++;
            }else{
                res.dat.emplace_back(r.dat[j]);
                j++;
            }
            p++;
            ok.emplace_back(false);
            if(p>=3){
                if(res.dat[p-2]+res.dat[p-3]>res.dat[p-1]){
                    if(id==-1)id=p-1;
                    ok[p-1]=true;
                }
            }
            if(id!=-1&&p>=6){
                if(id<p-3){
                    if(res.dat[p-2]+res.dat[p-3]>res.dat[p-1]){
                        res.ok=true;
                        return res;
                    }
                }
                if(ok[p-3]){
                    int x=p-3;
                    ll tot=res.dat[x-1]+res.dat[x-2]+res.dat[x-3]+res.dat[p-2];
                    for(int i=x-1;i>=x-3;i--){
                        ll cur=res.dat[i]+res.dat[p-2];
                        if(cur>res.dat[p-1]&&tot-cur>res.dat[x]){
                            res.ok=true;
                            return res;
                        }
                    }
                }
                if(ok[p-2]){
                    int x=p-2;
                    ll tot=res.dat[x-1]+res.dat[x-2]+res.dat[x-3]+res.dat[x-4];
                    for(int i=x-1;i>=x-4;i--){
                        for(int j=i-1;j>=x-4;j--){
                            ll cur=res.dat[i]+res.dat[j];
                            if(cur>res.dat[p-1]&&tot-cur>res.dat[x]){
                                res.ok=true;
                                return res;
                            }
                        }
                    }
                }
            }
        }
        return res;
    }
    void build(int l,int r,int i){
        if(l==r){
            t[i].dat.emplace_back(a[l]);
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=merge(t[i*2],t[i*2+1]);
    }
    Node query(int l,int r,int i,int x,int y){
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        if(y<=m)return query(l,m,i*2,x,y);
        if(x>=m+1)return query(m+1,r,i*2+1,x,y);
        return merge(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    seg.build(1,n,1);
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << (seg.query(1,n,1,l,r).ok?"YES":"NO") << "\n";
    }
}