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

const int K=1<<22;
const int N=2e6+5;

void dfs(int u);

struct SegTree{

vi t[K];
bitset<K> vis,vis2;

void build(int l,int r,int i){
    t[i].clear();
    vis[i]=vis2[i]=false;
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,i*2);
    build(m+1,r,i*2+1);
}

void update(int l,int r,int i,int x,int y,int v){
    if(y<l||r<x)return;
    if(x<=l&&r<=y){
        t[i].emplace_back(v);
        return;
    }
    int m=(l+r)/2;
    update(l,m,i*2,x,y,v);
    update(m+1,r,i*2+1,x,y,v);
}

void query(int l,int r,int i,int x,int y){
    if(y<l||r<x||vis2[i])return;
    if(!vis[i]){
        vis[i]=true;
        for(auto u:t[i])dfs(u);
    }
    if(x<=l&&r<=y)vis2[i]=true;
    if(l==r)return;
    int m=(l+r)/2;
    query(l,m,i*2,x,y);
    query(m+1,r,i*2+1,x,y);
}

}sl,sr;

int n;
int l[N],r[N];
bool vis[N];

void dfs(int u){
    if(vis[u])return;
    vis[u]=true;
    sr.query(1,n,1,u-r[u],u-l[u]);
    sl.query(1,n,1,u+l[u],u+r[u]);
}

void runcase(){
    cin >> n;
    sl.build(1,n,1);
    sr.build(1,n,1);
    for(int i=1;i<=n;i++)vis[i]=false;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i];
        sl.update(1,n,1,i-r[i],i-l[i],i);
        sr.update(1,n,1,i+l[i],i+r[i],i);
    }
    int ans=0;
    for(int i=1;i<=n;i++)if(!vis[i]){
        dfs(i);
        ans++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}