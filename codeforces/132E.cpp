#include "template.hpp"
#include "flow/min-cost-flow.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    MinCostFlow<int,int> mcf(2*n+3);
    int s=2*n,t=s+1,t2=t+1;
    for(int i=0;i<n;i++){
        mcf.addEdge(i*2,i*2+1,1,-100*n);
        mcf.addEdge(s,i*2,1,__builtin_popcount(a[i]));
        mcf.addEdge(i*2+1,t,1,0);
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            mcf.addEdge(i*2+1,j*2,1,a[i]==a[j]?0:__builtin_popcount(a[j]));
        }
    }
    mcf.addEdge(s,t,m,0);
    mcf.addEdge(t,t2,m,0);
    auto [f,c]=mcf.flow(s,t2);
    c+=100*n*n;
    PQ<pair<int,char>> pq;
    int p=0;
    for(auto i:mcf.adj[s]){
        auto e=mcf.e[i];
        if(e.flow>0&&e.to<s)pq.emplace(e.to/2,p++);
    }
    vector<int> val(n,-1);
    vector<pair<int,int>> ans;
    for(int i=0;i<n;i++){
        assert(!pq.empty());
        auto [x,p]=pq.top();
        pq.pop();
        assert(i==x);
        if(val[p]!=a[i]){
            val[p]=a[i];
            ans.eb(p,a[i]);
        }
        ans.eb(p,-1);
        for(auto j:mcf.adj[i*2+1]){
            auto e=mcf.e[j];
            if(e.flow>0&&e.to<s)pq.emplace(e.to/2,p);
        }
    }
    cout << SZ(ans) << " " << c << "\n";
    for(auto [p,v]:ans){
        if(v==-1){
            cout << "print(" << char('a'+p) << ")\n";
        }else{
            cout << char('a'+p) << "=" << v << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}