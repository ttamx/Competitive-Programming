#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,q,idx;
vector<ll> ans;
int a[N],p[N],lv[N];
vector<int> pa;
vector<int> adj[N];
vector<int> vec[N],res;
map<pair<int,int>,int> mp;
vector<pair<int,int>> qr;

void dfs(int u){
    for(auto v:adj[u]){
        lv[v]=lv[u]+1;
        dfs(v);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=2;i<=n;i++){
        cin >> p[i];
        adj[p[i]].emplace_back(i);
    }
    lv[1]=1;
    dfs(1);
    qr.resize(q+1);
    ans.resize(q+1);
    pa.resize(q+1);
    int idx=q;
    for(int i=1;i<=q;i++){
        auto &[x,y]=qr[i];
        cin >> x >> y;
        if(x>y)swap(x,y);
        auto it=mp.find({x,y});
        if(it!=mp.end()){
            pa[it->second]=i;
            ans[it->second]=0;
            it->second=i;
            ans[i]=1ll*a[x]*a[y];
        }else{
            mp[{x,y}]=i;
            ans[i]=1ll*a[x]*a[y];
        }
    }
    for(auto [x,y]:mp)vec[lv[x.second]].emplace_back(y);
    for(int i=n;i>=1;i--){
        vector<int> tmp;
        for(auto j:vec[i])res.emplace_back(j);
        for(auto j:res){
            auto [x,y]=qr[j];
            x=p[x],y=p[y];
            if(x>y)swap(x,y);
            auto it=mp.find({x,y});
            if(it!=mp.end()){
                pa[j]=it->second;
            }else{
                tmp.emplace_back(++idx);
                mp[{x,y}]=idx;
                pa[j]=idx;
                qr.emplace_back(x,y);
                pa.emplace_back(0);
                ans.emplace_back(1ll*a[x]*a[y]);
            }
        }
        res=tmp;
    }
    for(int i=idx;i>=1;i--)ans[i]+=ans[pa[i]];
    for(int i=1;i<=q;i++)cout << ans[i] << '\n';
}