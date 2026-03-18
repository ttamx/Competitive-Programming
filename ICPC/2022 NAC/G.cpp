#include<bits/stdc++.h>

using namespace std;

const int N=505;

int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int dir[256];

int n,m;
string a[N];
vector<pair<int,int>> adj[N][N];
bool vis[N][N];
int cnt[N][N],id[N][N];
int ans=0,uniq=0,buf=0;
pair<int,int> nxt[N][N];

void update(int x,int y,int v){
    for(int d=0;d<4;d++){
        int xx=x+dx[d];
        int yy=y+dy[d];
        if(a[xx][yy]=='#'){
            if(cnt[xx][yy]>0)uniq--;
            cnt[xx][yy]+=v;
            if(cnt[xx][yy]>0)uniq++;
        }
    }
}

void dfs(int x,int y){
    update(x,y,+1);
    ans=max(ans,uniq);
    for(auto [xx,yy]:adj[x][y]){
        if(!vis[xx][yy]){
            dfs(xx,yy);
        }
    }
    update(x,y,-1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    a[0]=string(m+2,'.');
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]="."+a[i]+".";
    }
    a[n+1]=string(m+2,'.');
    dir['>']=1;
    dir['v']=2;
    dir['<']=3;
    dir['^']=4;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(dir[a[i][j]]){
                int x=i+dx[dir[a[i][j]]-1];
                int y=j+dy[dir[a[i][j]]-1];
                if(dir[a[x][y]]){
                    nxt[i][j]={x,y};
                    adj[x][y].emplace_back(i,j);
                }else{
                    nxt[i][j]={i,j};
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(id[i][j]||!dir[a[i][j]])continue;
            buf++;
            int x=i,y=j;
            while(!id[x][y]){
                id[x][y]=buf;
                tie(x,y)=nxt[x][y];
            }
            if(id[x][y]!=buf)continue;
            vector<pair<int,int>> cyc;
            int xx=x,yy=y;
            do{
                cyc.emplace_back(x,y);
                tie(x,y)=nxt[x][y];
            }while(xx!=x||yy!=y);
            for(auto [x,y]:cyc){
                update(x,y,+1);
                vis[x][y]=true;
            }
            for(auto [x,y]:cyc){
                dfs(x,y);
            }
            for(auto [x,y]:cyc){
                update(x,y,-1);
            }
        }
    }
    cout << ans << "\n";
}