#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    while(cin >> n >> m){
        vector<int> mp(n+m+1),pa(n+m+1),sz(n+m+1),sum(n+m+1);
        for(int i=1;i<=n+m;i++)mp[i]=pa[i]=i;
        for(int i=1;i<=n;i++){
            sz[i]=1;
            sum[i]=i;
        }
        function<int(int)> fp=[&](int u){
            if(pa[u]==u)return u;
            return pa[u]=fp(pa[u]);
        };
        auto merge=[&](int u,int v){
            u=fp(u),v=fp(v);
            if(u==v)return;
            pa[v]=u;
            sz[u]+=sz[v];
            sum[u]+=sum[v];
            sz[v]=0;
            sum[v]=0;
        };
        int idx=n;
        while(m--){
            int o;
            cin >> o;
            if(o==1){
                int x,y;
                cin >> x >> y;
                merge(mp[x],mp[y]);
            }else if(o==2){
                int x,y;
                cin >> x >> y;
                int u=fp(mp[x]);
                int v=fp(mp[y]);
                if(u==v)continue;
                sz[u]--;
                sum[u]-=x;
                mp[x]=++idx;
                sz[idx]=1;
                sum[idx]=x;
                merge(v,idx);
            }else{
                int x;
                cin >> x;
                x=fp(mp[x]);
                cout << sz[x] << ' ' << sum[x] << '\n';
            }
        }
    }
}