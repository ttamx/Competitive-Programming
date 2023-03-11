#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1005;

int n,m,ans;
bool lnk[N][N];
vector<p2> edg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;++i){
        int u,v;
        cin >> u >> v;
        lnk[u][v]=lnk[v][u]=true;
        edg.emplace_back(u,v);
    }
    for(auto [u,v]:edg){
        int cnt=0;
        for(int i=1;i<=n;++i)if(lnk[u][i]&&lnk[v][i])++cnt;
        ans+=cnt*(cnt-1)/2;
    }
    int cnt=0;
    for(int i=0;i<m;++i){
        auto [a,b]=edg[i];
        for(int j=i+1;j<m;++j){
            auto [c,d]=edg[j];
            if(lnk[a][c]&&lnk[a][d]&&lnk[b][c]&&lnk[b][d])++cnt;
        }
    }
    ans-=cnt/3*5;
    cout << ans;
}
