#include "template.hpp"
#include "flow/dinic.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    vector<vector<pair<int,int>>> factor(n);
    vector<map<int,int>> id(n);
    int cur_id=n+2;
    for(int i=0;i<n;i++){
        cin >> a[i];
        int x=a[i];
        for(int d=2;d*d<=x;d++){
            if(x%d==0){
                int cnt=0;
                while(x%d==0){
                    cnt++;
                    x/=d;
                }
                factor[i].emplace_back(d,cnt);
                id[i][d]=cur_id++;
            }
        }
        if(x>1){
            factor[i].emplace_back(x,1);
            id[i][x]=cur_id++;
        }
    }
    Dinic<int> mf(cur_id+2,cur_id,cur_id+1);
    for(int i=0;i<n;i++){
        if(i%2==0){
            for(auto [d,c]:factor[i]){
                mf.add_edge(mf.s,id[i][d],c);
            }
        }else{
            for(auto [d,c]:factor[i]){
                mf.add_edge(id[i][d],mf.t,c);
            }
        }
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(u%2==1){
            swap(u,v);
        }
        for(auto [d,idx]:id[u]){
            if(id[v].count(d)){
                mf.add_edge(idx,id[v][d],INF);
            }
        }
    }
    cout << mf.flow() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}