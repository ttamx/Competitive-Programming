#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<ll,int,int,int,int>;

const int N=105;

int a,b,c;
ll dp[3][N][N][N];
priority_queue<T,vector<T>,greater<T>> pq;

inline void push(ll d,int i,int x,int y,int z){
    if(d<dp[i][x][y][z]){
        pq.emplace(dp[i][x][y][z]=d,i,x,y,z);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a,b,c;
    cin >> a >> b >> c;
    for(int i=0;i<3;i++){
        for(int x=0;x<a;x++){
            for(int y=0;y<b;y++){
                for(int z=0;z<c;z++){
                    dp[i][x][y][z]=LLONG_MAX;
                }
            }
        }
    }
    push(0,0,0,0,0);
    while(!pq.empty()){
        auto [d,i,x,y,z]=pq.top();
        pq.pop();
        if(i==2){
            cout << d+c/2 << "\n";
            exit(0);
        }
        if(d>dp[i][x][y][z])continue;
        if(i==0){
            int xx=(x+a/2)%a;
            int yy=(y-a/2+100*b)%b;
            int zz=(z+a/2)%c;
            if(yy>=x){
                push(d+a/2,1,xx,yy,zz);
            }else{
                xx=(xx+a/2)%a;
                yy=(yy-a/2+100*b)%b;
                zz=(zz+a/2)%c;
                push(d+a,0,xx,yy,zz);
            }
        }else{
            int xx=(x+b/2)%a;
            int yy=(y-b/2+100*b)%b;
            int zz=(z+b/2)%c;
            if(zz>=y){
                push(d+b/2,2,xx,yy,zz);
            }else{
                xx=(xx+b/2)%a;
                yy=(yy-b/2+100*b)%b;
                zz=(zz+b/2)%c;
                if((xx+a/2)%a>=y){
                    xx=(xx+a/2)%a;
                    yy=(yy-a/2+100*b)%b;
                    zz=(zz+a/2)%c;
                    push(d+b+a/2,0,xx,yy,zz);
                }else{
                    push(d+b,1,xx,yy,zz);
                }
            }
        }
    }
    cout << -1 << "\n";
}