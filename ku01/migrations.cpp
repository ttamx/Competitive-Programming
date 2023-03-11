#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int h,w,n;
    cin >> h >> w >> n;
    vector<vector<int>> g(h);
    for(auto &v:g){
        v.resize(w);
        for(auto &x:v){
            char c;
            cin >> c;
            x=(c=='#');
        }
    }
    int dx[4]={1,0,-1,0};
    int dy[4]={0,1,0,-1};
    while(n--){
        int a,b,c,d,e;
        cin >> a >> b >> c >> d >> e;
        a--,b--,c--,d--;
        vector<vector<int>> vis=g;
        queue<pair<int,int>> q;
        q.emplace(a,b);
        bool done=false;
        while(!q.empty()){
            auto [x,y]=q.front();
            q.pop();
            if(vis[x][y])continue;
            vis[x][y]=true;
            if(x==c&&y==d){
                done=true;
                break;
            }
            for(int i=0;i<4;i++){
                int xx=x+dx[i],yy=y+dy[i];
                if(xx<max(0,a-e)||yy<0||xx>min(h-1,a+e)||yy>=w||vis[xx][yy])continue;
                q.emplace(xx,yy);
            }
        }
        cout << done << '\n';
    }
}