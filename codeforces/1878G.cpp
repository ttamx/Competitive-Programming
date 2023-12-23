#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,q;
int a[N];
int sp[18][N];
vector<int> adj[N];
int sz[N],lv[N],hv[N],pos[N],hd[N],pa[N];
int t;

void dfs(int u,int p=0){
    sz[u]=1;
    pa[u]=p;
    lv[u]=lv[p]+1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p=0){
    pos[u]=++t;
    if(hv[u]){
        hd[hv[u]]=hd[u];
        hld(hv[u],u);
    }
    for(auto v:adj[u]){
        if(v==p||v==hv[u])continue;
        hd[v]=v;
        hld(v,u);
    }
}

int rmq(int l,int r){
    if(l>r)swap(l,r);
    int k=31-__builtin_clz(r-l+1);
    return sp[k][l]|sp[k][r-(1<<k)+1];
}

int bsearch(int l,int r,int v){
    r++;
    while(l<r){
        int m=(l+r)/2;
        if((v|rmq(l,m))>v)r=m;
        else l=m+1;
    }
    return l;
}

int bsearch2(int l,int r,int v){
    l--;
    while(l<r){
        int m=(l+r+1)/2;
        if((v|rmq(r,m))>v)l=m;
        else r=m-1;
    }
    return l;
}

int query(int u,int v){
    vector<pair<int,int>> l,r;
    while(hd[u]!=hd[v]){
        if(lv[hd[u]]<lv[hd[v]])swap(u,v),swap(l,r);
        l.emplace_back(pos[hd[u]],pos[u]);
        u=pa[hd[u]];
    }
    if(lv[u]<lv[v])swap(u,v),swap(l,r);
    l.emplace_back(pos[v],pos[u]);
    vector<int> suf;
    suf.emplace_back(0);
    for(auto [l,r]:r)suf.emplace_back(suf.back()|rmq(l,r));
    reverse(r.begin(),r.end());
    reverse(l.begin(),l.end());
    for(auto [l,r]:l)suf.emplace_back(suf.back()|rmq(l,r));
    reverse(l.begin(),l.end());
    int sum=0,res=0;
    for(auto [l,r]:l){
        suf.pop_back();
        int pos=bsearch2(l,r,sum);
        while(pos>=l){
            sum|=rmq(r,pos);
            res=max(res,__builtin_popcount(sum)+__builtin_popcount(suf.back()|rmq(pos,l)));
            pos=bsearch2(l,r,sum);
        }
    }
    for(auto [l,r]:r){
        suf.pop_back();
        int pos=bsearch(l,r,sum);
        while(pos<=r){
            sum|=rmq(l,pos);
            res=max(res,__builtin_popcount(sum)+__builtin_popcount(suf.back()|rmq(pos,r)));
            pos=bsearch(l,r,sum);
        }
    }
    return res;
}

void runcase(){
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    t=0,hd[1]=1;
    dfs(1);
    hld(1);
    for(int i=1;i<=n;i++)sp[0][pos[i]]=a[i];
    for(int i=1;i<18;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            sp[i][j]=sp[i-1][j]|sp[i-1][j+(1<<(i-1))];
        }
    }
    cin >> q;
    while(q--){
        int x,y;
        cin >> x >> y;
        cout << query(x,y) << " ";
    }
    cout << "\n";
    for(int i=1;i<=n;i++)adj[i].clear();
    for(int i=1;i<=n;i++)hv[i]=0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}