#include "template.hpp"
#include "flow/dinic.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,c;
    cin >> n >> m >> c;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    auto enc=[&](int i,int j){
        return i*m+j;
    };
    ll base=0;
    Dinic<ll> mf(n*m+2,n*m,n*m+1);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int id=enc(i,j);
            base+=a[i][j];
            mf.add_edge(mf.s,id,a[i][j]);
            if(i>0&&j>0)mf.add_edge(id,enc(i-1,j-1),c);
            else mf.add_edge(id,mf.t,c);
            if(i>0&&j+1<m)mf.add_edge(id,enc(i-1,j+1),c);
            else mf.add_edge(id,mf.t,c);
        }
    }
    cout << base-mf.flow();
}