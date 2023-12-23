#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using namespace std;

const int N=2e6+5;

using pii = pair<int,int>;
using vi = vector<int>;
using vp = vector<pii>;
using ll = long long;

struct suffixarray{
    vi sa,lcp,rank;
    suffixarray(){}
    suffixarray(const vp &s){init(s);}
    void init(const vp &s){
        int n=sz(s)+1;
        sa=lcp=rank=vi(n);
        iota(1+all(sa),0);sa[0]=n-1;
        sort(1+all(sa),[&](int a,int b){return s[a].first<s[b].first;});
        for(int i=1;i<n;i++){
            int a=sa[i-1],b=sa[i];
            rank[b]=i>1&&s[a].first==s[b].first?rank[a]:i;
        }
        for(int k=1;k<n;k*=2){
            vi ps(sa),pr(rank),pos(n);
            iota(all(pos),0);
            for(int i:ps)if((i-=k)>=0)sa[pos[rank[i]]++]=i;
            for(int i=1;i<n;i++){
                int a=sa[i-1],b=sa[i];
                rank[b]=pr[a]==pr[b]&&pr[a+k]==pr[b+k]?rank[a]:i;
            }
        }
        for(int i=0,j,k=0;i<n-1;lcp[rank[i++]]=k)
            for(k&&k--,j=sa[rank[i]-1];s[i+k].first==s[j+k].first;k++);
    }
}sa;

struct DSU{
    vi p;
    DSU(){}
    DSU(int n){init(n);}
    void init(int n){
        p.resize(n);
        iota(all(p),0);
    }
    int fp(int u){return p[u]=u==p[u]?u:fp(p[u]);}
    bool uni(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        return p[u]=v,true;
    }
}dsu;

int n;
vp str;
vector<tuple<int,int,int>> edge;
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    dsu.init(n+2);
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(auto x:s)str.emplace_back(x,i);
        str.emplace_back(-i,-i);
    }
    str.pop_back();
    sa.init(str);
    for(int i=n+1;i<=sz(str);i++){
        int u=str[sa.sa[i-1]].second,v=str[sa.sa[i]].second,w=sa.lcp[i];
        if(u!=v)edge.emplace_back(w,u,v);
    }
    sort(edge.rbegin(),edge.rend());
    for(auto [w,u,v]:edge)if(dsu.uni(u,v))ans+=w;
    cout << ans << "\n";
}