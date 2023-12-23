#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

typedef tuple<ld,int,int,int> t4;

const int N=5005;
const int M=1e5+5;

int n,m,k;
vector<t4> edge;
vector<int> ans;

struct dsu_t{
    int p[N];
    void init(){
        iota(p,p+n+1,0);
    }
    int fp(int u){
        if(p[u]==u)return u;
        return p[u]=fp(p[u]);
    }
    bool uni(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        p[v]=u;
        return true;
    }
}dsu;

int calc(ld lambda){
    dsu.init();
    ans.clear();
    for(auto &[w,i,u,v]:edge)if(u==1||v==1)w+=lambda;
    sort(edge.begin(),edge.end());
    int cnt=0;
    for(auto [w,i,u,v]:edge)if(dsu.uni(u,v)){
        if(u==1||v==1)cnt++;
        ans.emplace_back(i);
    }
    for(auto &[w,i,u,v]:edge)if(u==1||v==1)w-=lambda;
    return cnt;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        edge.emplace_back(w,i,u,v);
    }
    ld l=-1e5,r=1e5;
    for(int t=0;t<100;t++){
        ld m=(l+r)/2;
        int res=calc(m);
        if(res==k){
            cout << ans.size() << "\n";
            for(auto x:ans)cout << x << " ";
            return 0;
        }
        if(res>=k)l=m;
        else r=m;
    }
    cout << -1 << "\n";
}