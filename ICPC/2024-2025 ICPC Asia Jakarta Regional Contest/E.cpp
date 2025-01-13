#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const ll MOD=998244353;
const int INF=1e9;

int n;
ll a[2][N];
ll pw[N],wl[N],wr[N];
ll ans;
int li[2][N],ri[2][N];
vector<tuple<ll,int,int>> event;
bool alive[2][N];

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

struct DSU{
    int l[N],r[N],p[N];
    int fp(int u){
        return p[u]=p[u]==u?u:fp(p[u]);
    }
    void init(){
        for(int i=1;i<=n;i++){
            l[i]=r[i]=p[i]=i;
        }
    }
    void merge(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return;
        l[u]=min(l[u],l[v]);
        r[u]=max(r[u],r[v]);
        p[v]=u;
    }
    pair<int,int> get(int u){
        u=fp(u);
        return {l[u],r[u]};
    }
}dsu[2];

ll calc(int l1,int r1,int l2,int r2){
    ll v1=(wl[r1]-wl[l1-1]+MOD)%MOD;
    ll v2=(wr[l2]-wr[r2+1]+MOD)%MOD;
    return v1*v2%MOD;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<2;i++){
        for(int j=1;j<=n;j++){
            cin >> a[i][j];
            event.emplace_back(a[i][j],i,j);
        }
    }
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2%MOD;
    }
    for(int i=1;i<=n;i++){
        wl[i]=(wl[i-1]-pw[max(i-2,0)])%MOD;
    }
    for(int i=n;i>=1;i--){
        wr[i]=(wr[i+1]-pw[max(n-i-1,0)])%MOD;
    }
    for(int t=0;t<2;t++){
        int o=t^1;
        vector<pair<ll,int>> s;
        s.emplace_back(INF,0);
        for(int i=1;i<=n;i++){
            while(s.back().first<=a[o][i]){
                s.pop_back();
            }
            s.emplace_back(a[o][i],i);
            int l=0,r=s.size()-1;
            while(l<r){
                int m=(l+r+1)/2;
                if(s[m].first>a[t][i])l=m;
                else r=m-1;
            }
            li[t][i]=s[l].second;
        }
        s.clear();
        s.emplace_back(INF,n+1);
        for(int i=n;i>=1;i--){
            while(s.back().first<=a[o][i]){
                s.pop_back();
            }
            s.emplace_back(a[o][i],i);
            int l=0,r=s.size()-1;
            while(l<r){
                int m=(l+r+1)/2;
                if(s[m].first>a[t][i])l=m;
                else r=m-1;
            }
            ri[t][i]=s[l].second;
        }
    }
    for(int i=0;i<2;i++){
        dsu[i].init();
    }
    sort(event.begin(),event.end());
    for(auto [v,t,i]:event){
        alive[t][i]=true;
        if(alive[t][i-1])dsu[t].merge(i-1,i);
        if(alive[t][i+1])dsu[t].merge(i,i+1);
        auto [l,r]=dsu[t].get(i);
        if(l<=li[t][i])ans=(ans+v*calc(l,li[t][i],i,r))%MOD;
        if(ri[t][i]<=r)ans=(ans+v*calc(l,i,ri[t][i],r))%MOD;
        if(l<=li[t][i]&&ri[t][i]<=r)ans=(ans-v*calc(l,li[t][i],ri[t][i],r)%MOD+MOD)%MOD;
    }
    cout << ans*binpow(pw[n],MOD-2)%MOD << "\n";
}