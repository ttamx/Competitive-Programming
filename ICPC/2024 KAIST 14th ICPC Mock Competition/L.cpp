#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = double;
using cd = complex<db>;
using vi = vector<int>;
using vl = vector<ll>;
using vc = vector<cd>;

const int MOD=1e9+7;
const db PI=acos(-1.l);
	
void fft(vc &a){
    int n=a.size(),L=31-__builtin_clz(n);
    vc rt(n);
    rt[1]=1;
    for(int k=2;k<n;k*=2){
        cd z=polar(db(1),PI/k);
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
    int n=a.size();
    vl c(n);
    for(int i=0;i<n;i++){
        for(int j=0;i+j<n;j++){
            c[i+j]=(c[i+j]+a[i]*b[j])%MOD;
        }
    }
    return c;
}

const int N=1e5+5;

int n,a,b;
vector<int> adj[N];

vector<ll> dfs(int u,int p){
    vector<ll> cur(b+1);
    cur[1]=1LL;
    for(auto v:adj[u]){
        if(v==p)continue;
        auto tmp=dfs(v,u);
        cur=conv(cur,tmp);
    }
    cur[0]=(cur[0]+cur[a]+cur[b])%MOD;
    cur[b]=0LL;
    return cur;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> a >> b;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cout << dfs(1,0)[0] << "\n";
}