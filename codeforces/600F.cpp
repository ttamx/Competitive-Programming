#include<bits/stdc++.h>

using namespace std;

const int N=2005;

int a,b,m,d;
int deg[N];
int match[N][N];
int ans[N][N];

void paint(int u,int v){
    int c1=-1,c2=-2;
    for(int i=1;i<=d;i++){
        if(match[u][i]==0)c1=i;
        if(match[v][i]==0)c2=i;
        if(c1==c2){
            match[u][c1]=v;
            match[v][c1]=u;
            return;
        }
    }
    assert(c1>0&&c2>0);
    int x=match[v][c1];
    int y=match[x][c2];
    match[u][c1]=v;
    match[v][c1]=u;
    match[v][c2]=x;
    match[x][c2]=v;
    match[x][c1]=0;
    if(y){
        match[y][c2]=0;
        paint(x,y);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> a >> b >> m;
    vector<pair<int,int>> edges(m);
    for(auto &[u,v]:edges){
        cin >> u >> v;
        v+=a;
        deg[u]++,deg[v]++;
    }
    for(int i=1;i<=a+b;i++){
        d=max(d,deg[i]);
    }
    for(auto [u,v]:edges){
        paint(u,v);
    }
    for(int i=1;i<=a;i++){
        for(int c=1;c<=d;c++){
            if(match[i][c]){
                ans[i][match[i][c]]=c;
            }
        }
    }
    cout << d << "\n";
    for(auto [u,v]:edges){
        cout << ans[u][v] << " ";
    }
}