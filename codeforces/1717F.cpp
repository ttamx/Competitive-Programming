#include "template.hpp"
#include "flow/dinic.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> s(n),a(n);
    for(auto &x:s){
        cin >> x;
    }
    for(auto &x:a){
        cin >> x;
    }
    vector<pair<int,int>> edges(m);
    for(auto &[u,v]:edges){
        cin >> u >> v;
        u--,v--;
        a[u]++,a[v]--;
    }
    for(int i=0;i<n;i++){
        if(s[i]==1){
            if(a[i]%2!=0){
                cout << "NO\n";
                return;
            }
            a[i]/=2;
        }
    }
    Dinic<ll> mf(n+3,n,n+1);
    int aux=n+2;
    for(auto [u,v]:edges){
        mf.add_edge(u,v,1);
    }
    ll pos=0,neg=0;
    for(int i=0;i<n;i++){
        if(s[i]==1){
            if(a[i]>0){
                mf.add_edge(mf.s,i,a[i]);
                pos+=a[i];
            }else{
                mf.add_edge(i,mf.t,-a[i]);
                neg-=a[i];
            }
        }else{
            mf.add_edge(aux,i,INF);
            mf.add_edge(i,aux,INF);
        }
    }
    if(pos>neg){
        mf.add_edge(aux,mf.t,pos-neg);
    }else{
        mf.add_edge(mf.s,aux,neg-pos);
    }
    ll flow=mf.flow();
    if(flow!=max(pos,neg)){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for(int i=0;i<m;i++){
        auto [u,v]=edges[i];
        if(mf.e[i*2].flow==1){
            swap(u,v);
        }
        cout << u+1 << " " << v+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}