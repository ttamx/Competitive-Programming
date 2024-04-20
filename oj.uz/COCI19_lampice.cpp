
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
using ull = unsigned long long;
 
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int N=5e5+5;
const ull BASE=29;
const ull BASE2=31;
const ull BASE3=998244353;
 
int n;
string s;
ull a[N];
vector<int> adj[N];
ull hsh[26],pw[N],pw2[N];
int sz[N];
bool used[N];
int len;
gp_hash_table<ull,bool> mp;

ull calc(ull x,ull y,ull z){
    return (x*BASE3+y)*BASE3+z;
}
 
void init(){
    for(int i=1;i<=n;i++)used[i]=false;
}
 
int get_sz(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=get_sz(v,u);
    return sz[u];
}
 
int centroid(int u,int cnt,int p=0){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}
 
bool dfs1(int u,int p,ull cur,ull rev,ull cur2,ull rev2,int sz){
    if(sz>len)return false;
    if(mp[calc(rev*pw[len-sz]-cur,rev2*pw2[len-sz]-cur2,len-sz)])return true;
    for(auto v:adj[u])if(v!=p&&!used[v]){
        if(dfs1(v,u,cur*BASE+a[v],rev+a[v]*pw[sz],cur2*BASE2+a[v],rev2+a[v]*pw2[sz],sz+1)){
            return true;
        }
    }
    return false;
}
 
void dfs2(int u,int p,ull cur,ull rev,ull cur2,ull rev2,int sz){
    if(sz>len)return;
    mp[calc(rev*pw[len-sz]-cur,rev2*pw2[len-sz]-cur2,sz)]=true;
    for(auto v:adj[u])if(v!=p&&!used[v]){
        dfs2(v,u,cur*BASE+a[v],rev+a[v]*pw[sz],cur2*BASE2+a[v],rev2+a[v]*pw2[sz],sz+1);
    }
}

bool dfs3(int u,int p,ull cur,ull rev,ull cur2,ull rev2,int sz){
    if(sz>len)return false;
    if(sz==len&&cur==rev&&cur2==rev2)return true;
    for(auto v:adj[u])if(v!=p&&!used[v]){
        if(dfs3(v,u,cur*BASE+a[v],rev+a[v]*pw[sz],cur2*BASE2+a[v],rev2+a[v]*pw2[sz],sz+1)){
            return true;
        }
    }
    return false;
}
 
bool decom(int u){
    u=centroid(u,get_sz(u));
    used[u]=true;
    if(dfs3(u,u,a[u],a[u],a[u],a[u],1))return true;
    mp.clear();
    for(auto v:adj[u])if(!used[v]){
        if(dfs1(v,u,a[v],a[v],a[v],a[v],1))return true;
        dfs2(v,u,a[u]*BASE+a[v],a[v]*BASE+a[u],a[u]*BASE2+a[v],a[v]*BASE2+a[u],2);
    }
    for(auto v:adj[u])if(!used[v]&&decom(v))return true;
    return false;
}

int solve1(){
    int l=0,r=(n-1)/2;
    while(l<r){
        int m=(l+r+1)/2;
        len=m*2+1;
        init();
        if(decom(1))l=m;
        else r=m-1;
    }
    return l*2+1;
}
 
int solve2(){
    int l=0,r=n/2;
    while(l<r){
        int m=(l+r+1)/2;
        len=m*2;
        init();
        if(decom(1))l=m;
        else r=m-1;
    }
    return l*2;
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<26;i++)hsh[i]=rng();
    cin >> n >> s;
    pw[0]=pw2[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*BASE;
    for(int i=1;i<=n;i++)pw2[i]=pw2[i-1]*BASE2;
    for(int i=1;i<=n;i++)a[i]=s[i-1]-'a'+1;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cout << max(solve1(),solve2());
}