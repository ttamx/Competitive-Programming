#include<bits/stdc++.h>

using namespace std;

const int N=505;

int n,m,k;
int a[N][N],b[N][N];
bool vis[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=k;i++){
        int x,y;
        cin >> x >> y;
        a[x][y]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            b[i][j]=1;
        }
    }
    int x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int l=0,r=k+1;
    for(int i=x1;i<=x2;i++){
        for(int j=y1;j<=y2;j++){
            b[i][j]=0;
            l=max(l,a[i][j]);
        }
    }
    while(l<r){
        int mid=(l+r)/2;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                vis[i][j]=false;
            }
        }
        bool flag=true;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j]||a[i][j]>mid)continue;
                int cnt=0,space=0;
                queue<pair<int,int>> q;
                auto go=[&](int ii,int jj){
                    if(1<=ii&&ii<=n&&1<=jj&&jj<=m&&!vis[ii][jj]&&a[ii][jj]<=mid){
                        vis[ii][jj]=true;
                        q.emplace(ii,jj);
                    }
                };
                go(i,j);
                while(!q.empty()){
                    auto [ii,jj]=q.front();
                    q.pop();
                    cnt+=(a[ii][jj]>0);
                    space+=b[ii][jj];
                    go(ii-1,jj);
                    go(ii,jj-1);
                    go(ii,jj+1);
                    go(ii+1,jj);
                }
                if(cnt>space){
                    flag=false;
                    break;
                }
            }
            if(!flag)break;
        }
        if(flag)r=mid;
        else l=mid+1;
    }
    cout << (l>k?-1:l) << "\n";
}