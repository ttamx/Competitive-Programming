#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m,y;
    cin >> n >> m >> y;
    vector a(n,vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[i][j];
        }
    }
    vector<tuple<int,int,int>> event;
    auto enc=[&](int i,int j){return i*m+j;};
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i>0){
                int h=max(a[i-1][j],a[i][j]);
                event.emplace_back(h,enc(i-1,j),enc(i,j));
            }
            if(j>0){
                int h=max(a[i][j-1],a[i][j]);
                event.emplace_back(h,enc(i,j-1),enc(i,j));
            }
            if(i==0||i==n-1||j==0||j==m-1){
                event.emplace_back(a[i][j],n*m,enc(i,j));
            }
        }
    }
    sort(event.begin(),event.end());
    vector<int> ans(y+1);
    DSU dsu(n*m+1);
    for(auto [t,u,v]:event){
        dsu.merge(u,v);
        if(t<=y)ans[t]=dsu.size(n*m);
    }
    ans[0]=1;
    for(int i=1;i<=y;i++)ans[i]=max(ans[i],ans[i-1]);
    for(int i=1;i<=y;i++)cout << n*m-ans[i]+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}