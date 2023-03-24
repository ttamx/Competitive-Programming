#include<bits/stdc++.h>

using namespace std;

int dx[4]={1,1,-1,-1};
int dy[4]={1,-1,1,-1};

void runcase(){
    int n,m,x1,y1,x2,y2;
    string s;
    cin >> n >> m >> x1 >> y1 >> x2 >> y2 >> s;
    int d;
    if(s=="DR")d=0;
    if(s=="DL")d=1;
    if(s=="UR")d=2;
    if(s=="UL")d=3;
    vector<vector<vector<bool>>> vis(n+1,vector<vector<bool>>(m+1,vector<bool>(4)));
    int ans=0;
    while(!vis[x1][y1][d]){
        vis[x1][y1][d]=true;
        if(x1==x2&&y1==y2)return void(cout << ans << '\n');
        int nx=x1+dx[d];
        int ny=y1+dy[d];
        int cnt=0;
        bool x=(nx==0||nx==n+1);
        bool y=(ny==0||ny==m+1);
        if(x&&y){
            if(d==0)d=3;
            else if(d==1)d=2;
            else if(d==2)d=1;
            else if(d==3)d=0;
            nx=x1+dx[d];
            ny=y1+dy[d];
            cnt=1;
        }
        if(nx<1||nx>n){
            d=(d+2)%4;
            cnt=1;
            nx=x1+dx[d];
            ny=y1+dy[d];
        }
        if(ny>m){
            d=(d+1)%4;
            cnt=1;
            nx=x1+dx[d];
            ny=y1+dy[d];
        }
        if(ny<1){
            d=(d+3)%4;
            cnt=1;
            nx=x1+dx[d];
            ny=y1+dy[d];
        }
        x1=nx;
        y1=ny;
        ans+=cnt;
    }
    cout << -1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}