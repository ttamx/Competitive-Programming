#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int K=15;

int n,k,m;
int last[N];
vector<int> c[K][N];
bool mark[N],vis[N];
vector<int> ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> m;
    for(int i=0;i<m;i++){
        int u,v,d;
        cin >> u >> v >> d;
        last[u]=max(last[u],d);
        last[v]=max(last[v],d);
        c[d][u].emplace_back(v);
        c[d][v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        if(last[i]>1)continue;
        vector<int> a{i};
        for(int d=1;d<=k;d++){
            vector<int> b;
            for(auto u:a){
                for(auto v:c[d][u]){
                    if(last[v]<d+2&&!vis[v]){
                        vis[v]=true;
                        b.emplace_back(v);
                    }
                }
            }
            for(auto x:b)vis[x]=false;
            a=move(b);
        }
        for(auto x:a)if(!mark[x]){
            mark[x]=true;
            ans.emplace_back(x);
        }
    }
    sort(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << "\n";
}