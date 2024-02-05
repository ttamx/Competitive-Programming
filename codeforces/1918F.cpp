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

int n,k;
vi adj[N];
int ans;
int dep[N],lv[N];
vector<int> ord,val;

void dfs(int u){
    for(auto v:adj[u]){
        lv[v]=lv[u]+1;
        dfs(v);
        dep[u]=max(dep[u],dep[v]+1);
    }
    sort(all(adj[u]),[&](int i,int j){
        return dep[i]<dep[j];
    });
}

void dfs2(int u){
    ord.emplace_back(u);
    for(auto v:adj[u]){
        dfs2(v);
        if(sz(ord)>1&&lv[u]<=lv[ord.back()]&&lv[ord.back()]<=lv[ord.end()[-2]])ord.pop_back();
        ord.emplace_back(u);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    ans=2*n-2;
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    dfs(1);
    dfs2(1);
    ord.pop_back();
    ans-=lv[ord.back()];
    ord.pop_back();
    for(int i=1;i<sz(ord);i++){
        int u=ord[i-1],v=ord[i];
        if(lv[u]<=lv[v])continue;
        int d=lv[u]-lv[v];
        if(lv[v]>=d)continue;
        val.emplace_back(lv[v]-d);
    }
    sort(all(val));
    for(int i=0;i<min(k,sz(val));i++)ans+=val[i];
    cout << ans;
}