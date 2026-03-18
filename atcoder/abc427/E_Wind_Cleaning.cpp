#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=15;
const int O=15;
const int G=50;

int n,m;
char g[G][G];
int a[G][G];
bool vis[G][G][N][N][N][N];
queue<tuple<int,int,int,int,int,int,int>> q;
int sx,sy;

inline void push(int x,int y,int xl,int xr,int yl,int yr,int d){
    xl=max(xl,x-O-(sx-1));
    xr=min(xr,x-O+(n-sx));
    yl=max(yl,y-O-(sy-1));
    yr=min(yr,y-O+(m-sy));
    if(!vis[x][y][xl][xr][yl][yr]&&(x-O<xl||x-O>xr||y-O<yl||y-O>yr||g[x][y]!='#')){
        q.emplace(x,y,xl,xr,yl,yr,d);
        vis[x][y][xl][xr][yl][yr]=true;
    }
}

int calc(int xl,int xr,int yl,int yr){
    xl--,yl--;
    return a[xr][yr]-a[xr][yl]-a[xl][yr]+a[xl][yl];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(int j=1;j<=m;j++){
            g[i+O][j+O]=s[j-1];
            if(g[i+O][j+O]=='T'){
                sx=i;
                sy=j;
            }else if(g[i+O][j+O]=='#'){
                a[i][j]++;
            }
        }
    }
    for(int i=1;i<N;i++){
        for(int j=1;j<N;j++){
            a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
        }
    }
    push(sx+O,sy+O,1,n,1,m,0);
    while(!q.empty()){
        auto [x,y,xl,xr,yl,yr,d]=q.front();
        q.pop();
        if(calc(xl,xr,yl,yr)==0){
            cout << d << "\n";
            exit(0);
        }
        push(x-1,y,xl,xr,yl,yr,d+1);
        push(x,y-1,xl,xr,yl,yr,d+1);
        push(x,y+1,xl,xr,yl,yr,d+1);
        push(x+1,y,xl,xr,yl,yr,d+1);
    }
    cout << -1 << "\n";
}