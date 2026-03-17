#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2005;

int n;
int a[N][N];
int b[N][N];
queue<pair<int,int>> q;

inline void push(int i,int j){
    if(i<0||i>=N||j<0||j>=N||a[i][j])return;
    a[i][j]=1;
    q.emplace(i,j);
}

inline int bfs(int x,int y){
    int res=0;
    push(x,y);
    while(!q.empty()){
        auto [i,j]=q.front();
        q.pop();
        res+=b[i][j];
        push(i-1,j);
        push(i,j-1);
        push(i,j+1);
        push(i+1,j);
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int xx,yy;
    cin >> xx >> yy;
    xx*=2,yy*=2;
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        x*=2,y*=2;
        if(x==xx){
            if(yy<y){
                for(;yy<y;yy++){
                    a[xx][yy]=1;
                }
            }else{
                for(;yy>y;yy--){
                    a[xx][yy]=1;
                }
            }
        }else{
            if(xx<x){
                for(;xx<x;xx++){
                    a[xx][yy]=1;
                }
            }else{
                for(;xx>x;xx--){
                    a[xx][yy]=1;
                }
            }
        }
    }
    for(int i=1;i<N;i+=2){
        for(int j=1;j<N;j+=2){
            b[i][j]=1;
        }
    }
    bfs(0,0);
    int ans=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            ans=max(ans,bfs(i,j));
        }
    }
    cout << ans << "\n";
}