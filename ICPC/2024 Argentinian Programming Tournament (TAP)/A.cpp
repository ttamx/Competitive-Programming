#include<bits/stdc++.h>

using namespace std;

bool a[9][9];

bool wining(array<int,9> g,int v){
    if(g[0]==v&&g[0]==g[1]&&g[0]==g[2])return true;
    if(g[3]==v&&g[3]==g[4]&&g[3]==g[5])return true;
    if(g[6]==v&&g[6]==g[7]&&g[6]==g[8])return true;
    if(g[0]==v&&g[0]==g[3]&&g[0]==g[6])return true;
    if(g[1]==v&&g[1]==g[4]&&g[1]==g[7])return true;
    if(g[2]==v&&g[2]==g[5]&&g[2]==g[8])return true;
    if(g[0]==v&&g[0]==g[4]&&g[0]==g[8])return true;
    if(g[2]==v&&g[2]==g[4]&&g[2]==g[6])return true;
    return false;
}

int solve(array<int,9> g,int v){
    auto check=[&](int x){
        for(int i=0;i<9;i++)if(a[x][i]&&g[i]==-1){
            return false;
        }
        return true;
    };
    int res=-1;
    bool placed=false;
    for(int i=0;i<9;i++)if(g[i]==-1&&check(i)){
        placed=true;
        int mem=g[i];
        g[i]=v;
        if(wining(g,v))return 1;
        res=max(res,-solve(g,v^1));
        g[i]=mem;
    }
    return placed?res:0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        a[v][u]=true;
    }
    int res=solve({-1,-1,-1,-1,-1,-1,-1,-1,-1},0);
    if(res==1)cout << "X";
    else if(res==-1)cout << "O";
    else cout << "E";
}