#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e6+5;

int n,m,k;
vector<vector<ll>> a;
vector<vector<bool>> ok;
vector<tuple<ll,int,int,int>> ord;
int p[N],sz[N];
ll ans;

int fp(int u){
    return p[u]=p[u]==u?u:fp(p[u]);
}

void uni(int i,int j,int x,int y){
    if(!ok[x][y])return;
    int u=fp(i*m+j),v=fp(x*m+y);
    if(u!=v){
        p[v]=u;
        sz[u]+=sz[v];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    a.assign(n+2,vector<ll>(m+2));
    ok.assign(n+2,vector<bool>(m+2));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> a[i][j];
            ord.emplace_back(a[i][j],1,i,j);
            if(k)ord.emplace_back(a[i][j]+k,0,i,j);
        }
    }
    sort(ord.rbegin(),ord.rend());
    for(int i=0;i<N;i++)p[i]=i,sz[i]=1;
    for(auto [h,t,i,j]:ord){
        set<int> id{fp(i*m+j)};
        auto add=[&](int x,int y){
            if(ok[x][y])id.emplace(fp(x*m+y));
        };
        add(i-1,j),add(i,j-1),add(i,j+1),add(i+1,j);
        int s=0;
        for(auto x:id)s+=sz[x];
        ans=max(ans,h*s);
        if(t){
            ok[i][j]=true;
            uni(i,j,i-1,j);
            uni(i,j,i,j-1);
            uni(i,j,i,j+1);
            uni(i,j,i+1,j);
        }
    }
    cout << ans;
}