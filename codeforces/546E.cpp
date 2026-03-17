#include "template.hpp"
#include "flow/dinic.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    int tot=accumulate(a.begin(),a.end(),0);
    if(accumulate(b.begin(),b.end(),0)!=tot){
        cout << "NO\n";
        exit(0);
    }
    Dinic<int> mf(n*2+2,n*2,n*2+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        mf.add_edge(u,v+n,100);
        mf.add_edge(v,u+n,100);
    }
    for(int i=0;i<n;i++){
        mf.add_edge(mf.s,i,a[i]);
        mf.add_edge(i,i+n,100);
        mf.add_edge(i+n,mf.t,b[i]);
    }
    if(mf.flow()!=tot){
        cout << "NO\n";
        exit(0);
    }
    vector<vector<int>> ans(n,vector<int>(n));
    for(int i=0;i<mf.e.size();i+=2){
        int u=mf.e[i+1].to;
        int v=mf.e[i].to;
        if(u<n&&v>=n){
            ans[u][v-n]+=mf.e[i].flow;
        }
    }
    cout << "YES\n";
    for(auto &v:ans){
        for(auto x:v){
            cout << x << " ";
        }
        cout << "\n";
    }
}