#include<bits/stdc++.h>

using namespace std;

const int INF=1e9;

void runcase(int n,int m){
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<pair<int,int>> source,sink;
    vector<vector<int>> dist(n,vector<int>(m));
    for(int i=0;i<m;i++)if(a[0][i]!='@'){
        source.emplace_back(0,i);
    }
    for(int i=1;i<n;i++)if(a[i][m-1]!='@'){
        source.emplace_back(i,m-1);
    }
    for(int i=0;i<m;i++)if(a[n-1][i]!='@'){
        sink.emplace_back(n-1,i);
    }
    for(int i=0;i<n-1;i++)if(a[i][0]!='@'){
        sink.emplace_back(i,0);
    }
    deque<pair<int,int>> q;
    vector<vector<bool>> vis(n,vector<bool>(m));
    for(auto [i,j]:source){
        dist[i][j]=(a[i][j]=='.');
        if(dist[i][j]){
            q.emplace_back(i,j);
        }else{
            q.emplace_front(i,j);
        }
        vis[i][j]=true;
    }
    while(!q.empty()){
        auto [i,j]=q.front();
        q.pop_front();
        int d=dist[i][j];
        for(int di=-1;di<=1;di++){
            for(auto dj=-1;dj<=1;dj++){
                int ni=i+di,nj=j+dj;
                if(ni<0||ni>=n||nj<0||nj>=m||vis[ni][nj]||a[ni][nj]=='@')continue;
                vis[ni][nj]=true;
                int w=(a[ni][nj]=='.');
                dist[ni][nj]=d+w;
                if(w){
                    q.emplace_back(ni,nj);
                }else{
                    q.emplace_front(ni,nj);
                }
            }
        }
    }
    int ans=INF;
    for(auto [i,j]:sink){
        if(!vis[i][j])continue;
        ans=min(ans,dist[i][j]);
    }
    cout << (ans<INF?ans:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(true){
        int n,m;
        cin >> n >> m;
        if(n==0&&m==0)break;
        runcase(n,m);
    }
}