#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

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

const int N=2e5+5;
const int K=1<<19;

int a[N],b[N];

struct SegTree{
    int n;
    int t[K];
    bool lz[K];
    void build(int l,int r,int i){
        lz[i]=false;
        if(l==r)return void(t[i]=a[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void init(int _n){
        n=_n;
        build(0,n-1,1);
    }
    void push(int l,int r,int i){
        if(!lz[i])return;
        t[i]=r-l+1-t[i];
        if(l<r){
            lz[i*2]^=true;
            lz[i*2+1]^=true;
        }
        lz[i]=false;
    }
    void toggle(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=true,push(l,r,i);
        int m=(l+r)/2;
        toggle(l,m,i*2,x,y);
        toggle(m+1,r,i*2+1,x,y);
        t[i]=t[i*2]+t[i*2+1];
    }
    void toggle(int x,int y){
        toggle(0,n-1,1,x,y);
    }
    int sum(){
        return t[1];
    }
    void dump(int l,int r,int i){
        push(l,r,i);
        if(l==r)return void(b[l]=t[i]);
        int m=(l+r)/2;
        dump(l,m,i*2);
        dump(m+1,r,i*2+1);
    }
    void dump(){
        dump(0,n-1,1);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    seg.init(n);
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int l,r;
            cin >> l >> r;
            if(l<=r){
                int li=l%n,ri=r%n;
                int lc=l/n,rc=r/n;
                if(lc==rc){
                    seg.toggle(li,ri);
                }else{
                    seg.toggle(li,n-1);
                    seg.toggle(0,ri);
                }
            }
        }else{
            int w;
            cin >> w;
                if(w%n!=0){
                int m=gcd(n,w);
                seg.dump();
                for(int i=0;i<m;i++){
                    a[i]=0;
                }
                for(int i=0;i<n;i++){
                    a[i%m]^=b[i];
                }
                seg.init(m);
                n=m;
            }
        }
        cout << min(seg.sum(),n-seg.sum()) << "\n";
    }
}