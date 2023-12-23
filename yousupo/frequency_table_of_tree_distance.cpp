#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;

const ld PI=acosl(-1);

namespace fft{
    typedef complex<ld> cd;
    typedef vector<cd> vc;
    void fft(vc &a){
        int n=a.size(),L=31-__builtin_clz(n);
        vc rt(n);
        rt[1]=1;
        for(int k=2;k<n;k*=2){
            cd z=polar(1.l,PI/k);
            for(int i=k;i<2*k;i++)rt[i]=i&1?rt[i/2]*z:rt[i/2];
        }
        vi rev(n);
        for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
        for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
        for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
            cd z=rt[j+k]*a[i+j+k];
            a[i+j+k]=a[i+j]-z;
            a[i+j]+=z;
        }
    }
    vl conv(const vl &a,const vl &b){
        if(a.empty()||b.empty())return {};
        vl res(a.size()+b.size()-1);
        int n=1<<(32-__builtin_clz(res.size()));
        vc in(n),out(n);
        copy(a.begin(),a.end(),in.begin());
        for(int i=0;i<b.size();i++)in[i].imag(b[i]);
        fft(in);
        for(auto &x:in)x*=x;
        for(int i=0;i<n;i++)out[i]=(in[-i&(n-1)]-conj(in[i]));
        fft(out);
        for(int i=0;i<res.size();i++)res[i]=imag(out[i])/(4*n)+.5;
        return res;
    }
}

const int N=2e5+5;

int n;
vi adj[N];
int sz[N],dep[N];
bool used[N];
vl cnt;
ll ans[N];

int getsz(int u,int p=-1){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=getsz(v,u);
    return sz[u];
}

int getdep(int u,int p=-1){
    dep[u]=0;
    for(auto v:adj[u])if(v!=p&&!used[v])dep[u]=max(dep[u],getdep(v,u));
    return ++dep[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,int d=1,int p=-1){
    cnt[d]++;
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,d+1,u);
}

void decom(int u){
    u=centroid(u,getsz(u));
    getdep(u);
    used[u]=true;
    sort(adj[u].begin(),adj[u].end(),[&](int i,int j){
        return dep[i]<dep[j];
    });
    vl cur(1,1);
    for(auto v:adj[u])if(!used[v]){
        cnt.assign(dep[v]+1,0);
        cur.resize(dep[v]+1);
        dfs(v);
        vl tmp=fft::conv(cur,cnt);
        for(int i=1;i<tmp.size();i++)ans[i]+=tmp[i];
        for(int i=0;i<cnt.size();i++)cur[i]+=cnt[i];
    }
    for(auto v:adj[u])if(!used[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    for(int i=1;i<n;i++)cout << ans[i] << " ";
}