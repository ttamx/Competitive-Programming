#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int N=2e5+5;
const int K=1<<19;

int a[N];

struct segtree{
    struct node{
        int l,r,mx;
        node(){}
        node(int l,int r,int mx):l(l),r(r),mx(mx){}
        friend node operator+(const node &lhs,const node &rhs){
            if(lhs.mx>rhs.mx)return lhs;
            if(lhs.mx<rhs.mx)return rhs;
            return node(lhs.l,rhs.r,lhs.mx);
        }
    }t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=node(l,l,a[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return node(0,0,0);
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}s;

void runcase(){
    int n;
    cin >> n;
    vector<vi> pos(n+2);
    vector<bool> used(n+2);
    set<int> pt;
    a[0]=a[n+1]=0;
    for(int i=1;i<=n;i++)cin >> a[i];
    s.build(1,n,1);
    bool ok=true;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        if(a[i]>x)ok=false;
        pos[x].emplace_back(i);
    }
    if(!ok)return void(cout << "NO\n");
    auto bsr=[&](int sl,int sr,int v){
        int l=sl,r=sr;
        while(l<r){
            int m=(l+r)/2;
            if(s.query(1,n,1,sl,m).mx>=v)r=m;
            else l=m+1;
        }
        return l;
    };
    auto bsl=[&](int sl,int sr,int v){
        int l=sl,r=sr;
        while(l<r){
            int m=(l+r+1)/2;
            if(s.query(1,n,1,m,sr).mx>=v)l=m;
            else r=m-1;
        }
        return l;
    };
    for(int i=n;i>=1;i--){
        for(int l=0,r=0;r<sz(pos[i]);l=++r){
            while(r+1<sz(pos[i])&&pos[i][r]+1==pos[i][r+1])r++;
            for(int j=pos[i][l];j<=pos[i][r];j++)used[j]=true;
            auto res=s.query(1,n,1,pos[i][l],pos[i][r]);
            if(res.mx==i){
                pt.emplace(res.l),pt.emplace(res.r);
                continue;
            }
            if(a[pos[i][r]+1]<=i&&used[pos[i][r]+1]){
                int p=*pt.lower_bound(pos[i][r]+1)-1;
                if(pos[i][r]+1<=p){
                    p=bsr(pos[i][r]+1,p,i);
                    if(s.query(1,n,1,pos[i][r]+1,p).mx==i){
                        pt.emplace(p);
                        continue;
                    }
                }
            }
            if(a[pos[i][l]-1]<=i&&used[pos[i][l]-1]){
                int p=*prev(pt.upper_bound(pos[i][l]-1))+1;
                if(p<=pos[i][l]-1){
                    p=bsl(p,pos[i][l]-1,i);
                    if(s.query(1,n,1,p,pos[i][l]-1).mx==i){
                        pt.emplace(p);
                        continue;
                    }
                }
            }
            return void(cout << "NO\n");
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}