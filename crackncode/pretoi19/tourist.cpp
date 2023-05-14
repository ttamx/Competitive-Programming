#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,k,q;
int sz[N],a[N],p[N];
pair<int,int> e[N];
map<int,int> mp;
tuple<int,int,int,int> qr[N];
int ans[N];
int cnt[N];

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

void uni(int u,int v){
    u=fp(u),v=fp(v);
    if(u==v)return;
    p[u]=v;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k >> q;
    for(int i=1;i<=k;i++){
        int x;
        cin >> x;
        a[x]++;
    }
    for(int i=1;i<N;i++){
        if(a[i]){
            sz[a[i]]++;
            mp[a[i]];
        }
    }
    int idx=0;
    for(auto &[x,y]:mp)y=++idx;
    for(int i=1;i<=m;i++){
        auto &[u,v]=e[i];
        cin >> u >> v;
    }
    for(int i=1;i<=q;i++){
        auto &[t,x,y,z]=qr[i];
        cin >> t;
        if(t==1){
            cin >> x >> y >> z;
        }else{
            cin >> x >> y;
        }
    }
    for(auto [val,idx]:mp){
        iota(p,p+n+1,0);
        for(int i=1;i<=q;i++){
            auto &[t,x,y,z]=qr[i];
            if(t==1&&y<=val&&val<=z){
                cnt[x]++;
            }
        }
        for(int i=1;i<=m;i++){
            if(cnt[i]==0){
                uni(e[i].first,e[i].second);
            }
        }
        for(int i=q;i>=1;i--){
            auto &[t,x,y,z]=qr[i];
            if(t==1&&y<=val&&val<=z){
                if(--cnt[x]==0){
                    uni(e[x].first,e[x].second);
                }
            }else{
                if(fp(x)==fp(y)){
                    ans[i]+=sz[val];
                }
            }
        }
    }
    for(int i=1;i<=q;i++){
        auto &[t,x,y,z]=qr[i];
        if(t==2){
            cout << ans[i] << "\n";
        }
    }
}