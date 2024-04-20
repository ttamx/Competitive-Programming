#include<bits/stdc++.h>

using namespace std;

struct Edge{
    int u,v,w;
};

int n,m;
vector<Edge> edges;

bool cmp(Edge l,Edge r){
    return l.w>r.w;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        Edge e;
        cin >> e.u >> e.v >> e.w;
        edges.push_back(e);
    }
    sort(edges.begin(),edges.end(),cmp);
    for(auto e:edges){
        cout << e.u << " " << e.v << " : " << e.w << "\n";
    }
}