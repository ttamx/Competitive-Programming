#include "template.hpp"
#include "data-structure/dsu.hpp"

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    auto enc=[&](int i,int j){
        return i*m+j;
    };
    map<int,vector<pair<int,int>>> mp;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            mp[-a[i][j]].emplace_back(i,j);
        }
    }
    DSU dsu(n*m);
    int cnt=0,ans=1;
    vector<bool> alive(n*m);
    auto work=[&](int x,int y,int i,int j){
        if(i<0||j<0||i>=n||j>=m||!alive[enc(i,j)])return;
        if(dsu.merge(enc(x,y),enc(i,j))){
            cnt--;
        }
    };
    for(auto &[_,v]:mp){
        for(auto [i,j]:v){
            cnt++;
            alive[enc(i,j)]=true;
        }
        for(auto [i,j]:v){
            work(i,j,i-1,j);
            work(i,j,i+1,j);
            work(i,j,i,j-1);
            work(i,j,i,j+1);
        }
        ans=max(ans,cnt);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}