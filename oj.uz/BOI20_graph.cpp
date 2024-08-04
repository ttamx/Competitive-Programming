#include<bits/stdc++.h>

using namespace std;

using db = double;

const int N=1e5+5;

int n,m;
vector<pair<int,int>> adj[N];
bool vis[N];
int a[N],b[N],ans[N];
vector<int> comp;
pair<int,int> val;
bool found;

void dfs(int u){
    comp.emplace_back(u);
    vis[u]=true;
    for(auto [v,w]:adj[u]){
        if(!vis[v]){
            a[v]=-a[u];
            b[v]=w-b[u];
            dfs(v);
        }else{
            if(a[u]+a[v]==0){
                if(b[u]+b[v]!=w){
                    cout << "NO",exit(0);
                }
            }else{
                int num=w-b[u]-b[v];
                int den=a[u]+a[v];
                if(!found){
                    found=true;
                    val={num,den};
                }else if(num*val.second!=val.first*den){
                    cout << "NO",exit(0);
                }
            }
        }
    }
}

inline int calc(int x){
    int res=0;
    for(auto u:comp){
        res+=abs(a[u]*x+b[u]);
    }
    return res;
}

inline void answer(int x){
    for(auto u:comp){
        ans[u]=a[u]*x+b[u];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        w*=2;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=1;i<=n;i++)if(!vis[i]){
        comp.clear();
        found=false;
        a[i]=1,b[i]=0;
        dfs(i);
        if(found){
            answer(val.first/val.second);
        }else{
            int c=comp.size();
            int l=-c*2,r=c*2;
            while(l<r){
                int m=l+(r-l)/2;
                if(calc(m)<calc(m+1))r=m;
                else l=m+1;
            }
            answer(l);
        }
    }
    cout << "YES\n";
    for(int i=1;i<=n;i++){
        if(ans[i]<0)cout << '-';
        cout << abs(ans[i])/2 << '.' << "05"[ans[i]&1] << ' ';
    }
}