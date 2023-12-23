#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int M=10005;
const int inf=1e9;

int n,m;
int pos[N];
vector<pair<int,int>> edge;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)pos[i]=i;
    tuple<int,int,int> mn(inf,-1,-1);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        edge.emplace_back(u,v);
        mn=min(mn,{w,u,v});
    }
    auto [w,s,e]=mn;
    pos[s]=-inf;
    pos[e]=inf;
    cout << w << " 1\n";
    for(auto [u,v]:edge){
        if(u==s&&v==e){
            cout << u << " " << v << " 1\n";
        }else{
            if(pos[u]<pos[v])swap(u,v);
            cout << u << " " << v << " 0\n";
        }
    }
}