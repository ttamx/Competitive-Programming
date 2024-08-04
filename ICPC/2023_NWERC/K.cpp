#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int a[2],b[2];
    for(int i=0;i<2;i++)cin >> a[i] >> b[i];
    vector vis(n,vector(n,vector<bool>(2)));
    queue<tuple<int,int,int>> q;
    q.emplace(0,0,0);
    q.emplace(0,0,1);
    vis[0][0][0]=vis[0][0][1]=true;
    while(!q.empty()){
        auto [i,j,s]=q.front();
        q.pop();
        for(auto mi:{-1,1}){
            for(auto mj:{-1,1}){
                for(int k=0;k<2;k++){
                    int dx=mi*(k?a[s]:b[s]);
                    int dy=mj*(k?b[s]:a[s]);
                    int ni=i+dx,nj=j+dy;
                    if(ni<0||ni>=n||nj<0||nj>=n)continue;
                    if(vis[ni][nj][s^1])continue;
                    vis[ni][nj][s^1]=true;
                    q.emplace(ni,nj,s^1);
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans+=(vis[i][j][0]||vis[i][j][1]);
    cout << ans;
}