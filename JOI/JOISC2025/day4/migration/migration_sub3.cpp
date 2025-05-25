#include<bits/stdc++.h>

using namespace std;

const int N=2e6+5;

int n,q;
int p[N],a[N],dep[N];
vector<int> ids[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=2;i<=n;i++){
        cin >> p[i];
        dep[i]=dep[p[i]]+1;
        ids[dep[i]].emplace_back(i);
    }
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int x,y;
            cin >> x >> y;
            for(auto u:ids[x]){
                int v=u;
                while(dep[v]>y)v=p[v];
                a[v]+=a[u];
                a[u]=0;
                ids[y].emplace_back(v);
            }
            ids[x].clear();
        }else if(t==2){
            int u,x;
            cin >> u >> x;
            a[u]+=x;
            ids[dep[u]].emplace_back(u);
        }else{
            int u;
            cin >> u;
            cout << a[u] << "\n";
        }
    }
}