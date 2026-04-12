#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int K=1<<20;
const ll INF=1e18;

int n,q;
ll k;
ll a[N];
vector<pair<int,int>> qr[N];
int fa[N],sz[N];
ll b[N],ans[N];
set<pair<ll,int>> s;

int fp(int u){
    while(fa[u]!=u)u=fa[u];
    return u;
}

ll query(int u){
    ll res=b[u];
    while(fa[u]!=u)res+=b[u=fa[u]];
    return res;
}

int merge(int u,int v){
    u=fp(u),v=fp(v);
    assert(u!=v);
    if(sz[u]<sz[v])swap(u,v);
    fa[v]=u;
    b[v]-=b[u];
    sz[u]+=sz[v];
    return u;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    ll lz=0;
    for(int i=1;i<=n;i++){
        b[i]=-lz;
        fa[i]=i;
        sz[i]=1;
        s.emplace((-lz%k+k)%k,i);
        if(i%2==0){
            ll l=(-lz%k+k)%k;
            ll r=(l+a[i]-1)%k;
            if(a[i]>=k){
                l=0;
                r=k-1;
            }
            if(l<=r){
                int u=0;
                auto it=s.lower_bound(make_pair(l,0));
                while(it!=s.end()&&it->first<=r){
                    auto [val,v]=*it;
                    b[v]+=a[i]-(val+lz%k+k)%k;
                    if(!u)u=v;
                    else u=merge(u,v);
                    it=s.erase(it);
                }
                lz-=a[i];
                if(u)s.emplace((-lz%k+k)%k,u);
            }else{
                int u=0;
                auto it=s.lower_bound(make_pair(l,0));
                while(it!=s.end()){
                    auto [val,v]=*it;
                    b[v]+=a[i]-(val+lz%k+k)%k;
                    if(!u)u=v;
                    else u=merge(u,v);
                    it=s.erase(it);
                }
                it=s.begin();
                while(it!=s.end()&&it->first<=r){
                    auto [val,v]=*it;
                    b[v]+=a[i]-(val+lz%k+k)%k;
                    if(!u)u=v;
                    else u=merge(u,v);
                    it=s.erase(it);
                }
                lz-=a[i];
                if(u)s.emplace((-lz%k+k)%k,u);
            }
        }else{
            lz+=a[i];
        }
        for(auto [x,j]:qr[i]){
            ans[j]=query(x)+lz;
        }
    }
    for(int i=1;i<=q;i++){
        cout << ans[i]/k << "\n";
    }
}