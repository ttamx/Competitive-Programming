#include<bits/stdc++.h>

using namespace std;

const int N=1505;

int h,w,k,l;
int xh,yh,xv,yv;
int top[N][N],bot[N][N],lef[N][N],rig[N][N];
string a[N];
queue<pair<int,int>> q;
bool vis[N][N];

bool checkh(int i1,int j1,int i2,int j2){
    int l1=max(lef[i1][j1],j1-k);
    int r1=min(rig[i1][j1],j1+k);
    int l2=max(lef[i2][j2],j2-k);
    int r2=min(rig[i2][j2],j2+k);
    return min(r1,r2)-max(l1,l2)-1>=k;
}

bool checkv(int i1,int j1,int i2,int j2){
    int l1=max(top[i1][j1],i1-l);
    int r1=min(bot[i1][j1],i1+l);
    int l2=max(top[i2][j2],i1-l);
    int r2=min(bot[i2][j2],i1+l);
    return min(r1,r2)-max(l1,l2)-1>=l;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> w >> h >> k >> l;
    cin >> xh >> yh >> xv >> yv;
    for(int i=0;i<h;i++)cin >> a[i];
    for(int i=0;i<h;i++){
        lef[i][0]=a[i][0]=='X'?0:-1;
        for(int j=1;j<w;j++)lef[i][j]=a[i][j]=='X'?j:lef[i][j-1];
    }
    for(int i=0;i<h;i++){
        rig[i][w-1]=a[i][w-1]=='X'?w-1:w;
        for(int j=w-2;j>=0;j--)rig[i][j]=a[i][j]=='X'?j:rig[i][j+1];
    }
    for(int j=0;j<w;j++)top[0][j]=a[0][j]=='X'?0:-1;
    for(int i=1;i<h;i++)for(int j=0;j<w;j++)top[i][j]=a[i][j]=='X'?i:top[i-1][j];
    for(int j=0;j<w;j++)bot[h-1][j]=a[h-1][j]=='X'?h-1:h;
    for(int i=h-2;i>=0;i--)for(int j=0;j<w;j++)bot[i][j]=a[i][j]=='X'?i:bot[i+1][j];
    vis[yh][xv]=true;
    q.emplace(yh,xv);
    while(!q.empty()){
        auto [i,j]=q.front();
        q.pop();
        if(a[i][j]=='*')cout << "YES",exit(0);
        if(j+1<w&&!vis[i][j+1]&&checkv(i,j,i,j+1)){
            vis[i][j+1]=true;
            q.emplace(i,j+1);
        }
        if(j>0&&!vis[i][j-1]&&checkv(i,j,i,j-1)){
            vis[i][j-1]=true;
            q.emplace(i,j-1);
        }
        if(i+1<h&&!vis[i+1][j]&&checkh(i,j,i+1,j)){
            vis[i+1][j]=true;
            q.emplace(i+1,j);
        }
        if(i>0&&!vis[i-1][j]&&checkh(i,j,i-1,j)){
            vis[i-1][j]=true;
            q.emplace(i-1,j);
        }
    }
    cout << "NO";
}