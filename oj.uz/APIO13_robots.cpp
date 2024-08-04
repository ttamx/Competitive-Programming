#include<bits/stdc++.h>

using namespace std;

const int N=10;
const int H=500;
const int INF=1e9;

int n,h,w;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
string a[H];
pair<int,int> pos[H][H][4];
bool vis[H][H][4];
int dp[N][N][H][H];

pair<int,int> dfs(int i,int j,int d){
    if(i<0||i>=h||j<0||j>=w||a[i][j]=='x')return {-1,-1};
    if(vis[i][j][d])return pos[i][j][d];
    vis[i][j][d]=true;
    int nd=d;
    if(a[i][j]=='C')nd=(nd+1)%4;
    if(a[i][j]=='A')nd=(nd+3)%4;
    pos[i][j][d]=dfs(i+dx[nd],j+dy[nd],nd);
    if(pos[i][j][d]==make_pair(-1,-1))pos[i][j][d]={i,j};
    return pos[i][j][d];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> w >> h;
    for(int i=0;i<h;i++)cin >> a[i];
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            for(int d=0;d<4;d++){
                dfs(i,j,d);
            }
        }
    }
    for(int l=0;l<n;l++){
        for(int r=l;r<n;r++){
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    dp[l][r][i][j]=INF;
                }
            }
        }
    }
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(isdigit(a[i][j])){
                int x=a[i][j]-'1';
                auto &dp2=dp[x][x];
                dp2[i][j]=0;
                queue<pair<int,int>> q;
                q.emplace(i,j);
                while(!q.empty()){
                    auto [i,j]=q.front();
                    q.pop();
                    for(int d=0;d<4;d++){
                        pair<int,int> p=pos[i][j][d];
                        if(dp2[p.first][p.second]>dp2[i][j]+1){
                            dp2[p.first][p.second]=dp2[i][j]+1;
                            q.emplace(p);
                        }
                    }
                }
            }
        }
    }
    for(int s=1;s<n;s++){
        for(int l=0,r=s;r<n;l++,r++){
            auto &dp2=dp[l][r];
            for(int m=l;m<r;m++){
                for(int i=0;i<h;i++){
                    for(int j=0;j<w;j++){
                        dp2[i][j]=min(dp2[i][j],dp[l][m][i][j]+dp[m+1][r][i][j]);
                    }
                }
            }
            using T = tuple<int,int,int>;
            priority_queue<T,vector<T>,greater<T>> pq;
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    if(dp2[i][j]<INF){
                        pq.emplace(dp2[i][j],i,j);
                    }
                }
            }
            while(!pq.empty()){
                auto [d,i,j]=pq.top();
                pq.pop();
                if(d>dp2[i][j])continue;
                for(int k=0;k<4;k++){
                    auto [x,y]=pos[i][j][k];
                    if(dp2[x][y]>d+1){
                        dp2[x][y]=d+1;
                        pq.emplace(d+1,x,y);
                    }
                }
            }
        }
    }
    int ans=INF;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            ans=min(ans,dp[0][n-1][i][j]);
        }
    }
    cout << (ans==INF?-1:ans);
}