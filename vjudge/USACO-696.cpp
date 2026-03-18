#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int a[N],b[N];
vector<int> adj[N];
int add[N];
int timer=0;
vector<int> event[N];
int ans[N];

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}fw;

void dfs(int u){
    event[timer].emplace_back(-u);
    add[++timer]=a[u];
    for(auto v:adj[u])dfs(v);
    event[timer].emplace_back(u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    freopen("promote.in","r",stdin);
    freopen("promote.out","w",stdout);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]=b[i]=-a[i];
    }
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        fw.update(add[i],1);
        for(auto j:event[i]){
            if(j>0){
                ans[j]+=fw.query(a[j]-1);
            }else{
                j=-j;
                ans[j]-=fw.query(a[j]-1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout << ans[i] << "\n";
    }
}