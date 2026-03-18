#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<ll,int,int,int,int>;

const int N=105;

int a,b,c;
ll dp[6][N][N][N];
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
    for(int i=0;i<6;i++){
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
        if(i==5){
            cout << d << "\n";
            exit(0);
        }
        if(d>dp[i][x][y][z])continue;
        if(i/2==0){
            int xx=(x+a/2)%a;
            int yy=(y-a/2+100*b)%b;
            int zz=(z+a/2)%c;
            push(d+a/2,i^1,xx,yy,zz);
        }
        if(i/2==1){
            int xx=(x+b/2)%a;
            int yy=(y-b/2+100*b)%b;
            int zz=(z+b/2)%c;
            push(d+b/2,i^1,xx,yy,zz);
        }
        if(i/2==2){
            int xx=(x+c/2)%a;
            int yy=(y-c/2+100*b)%b;
            int zz=(z+c/2)%c;
            push(d+c/2,i^1,xx,yy,zz);
        }
        if(i==1){
            if((x+a/2)%a<=y){
                push(d,2,x,y,z);
            }
        }
        if(i==2){
            if((x+a/2)%a>=y){
                push(d,1,x,y,z);
            }
        }
        if(i==3){
            if((y+b/2)%b<=z){
                push(d,4,x,y,z);
            }
        }
        if(i==4){
            if((y+b/2)%b>=z){
                push(d,3,x,y,z);
            }
        }
    }
    cout << -1 << "\n";
}