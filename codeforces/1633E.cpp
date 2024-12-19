#include "template.hpp"
#include "data-structure/dsu.hpp"

const int X=1e8;

bitset<X> cnt;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> edges(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    sort(edges.begin(),edges.end());
    int p,k,a,b,c;
    cin >> p >> k >> a >> b >> c;
    int x;
    for(int i=0;i<k;i++){
        if(i<p){
            cin >> x;
        }else{
            x=(1LL*a*x+b)%c;
        }
        cnt[x]=!cnt[x];
    }
    vector<int> nxt(m),pre(m,-1);
    for(int i=0;i<m;i++){
        auto [w,u,v]=edges[i];
        auto &j=nxt[i];
        j=i+1;
        DSU dsu(n);
        for(;j<m;j++){
            auto [ww,uu,vv]=edges[j];
            dsu.merge(uu,vv);
            if(dsu.same(u,v)){
                break;
            }
        }
    }
    for(int i=0;i<m;i++){
        if(nxt[i]<m){
            pre[nxt[i]]=i;
        }
    }
    vector<tuple<ll,ll,ll>> event;
    for(int i=0;i<m;i++){
        if(pre[i]!=-1){
            ll l=get<0>(edges[pre[i]]);
            ll r=get<0>(edges[i]);
            ll mid=(l+r)/2+1;
            event.emplace_back(mid,-1,r-mid);
            event.emplace_back(r,1,0);
        }else{
            ll r=get<0>(edges[i]);
            event.emplace_back(0,-1,r);
            event.emplace_back(r,1,0);
        }
        if(nxt[i]!=m){
            ll l=get<0>(edges[i]);
            ll r=get<0>(edges[nxt[i]]);
            ll mid=(l+r)/2;
            event.emplace_back(mid,-1,0);
            event.emplace_back(mid+1,0,l-mid);
            event.emplace_back(l,1,0);
        }else{
            ll l=get<0>(edges[i]);
            event.emplace_back(l,1,0);
        }
    }
    sort(event.rbegin(),event.rend());
    ll slope=0,val=0,ans=0;
    for(int i=0;i<X;i++){
        val+=slope;
        while(!event.empty()&&get<0>(event.back())==i){
            auto [_,x,y]=event.back();
            slope+=x;
            val+=y;
            event.pop_back();
        }
        if(cnt[i]){
            ans^=val;
        }
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}