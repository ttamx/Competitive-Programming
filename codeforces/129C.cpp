#include<bits/stdc++.h>

using namespace std;

bool vis[9][8][8];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<string> a(8);
    for(auto &x:a)cin >> x;
    queue<tuple<int,int,int>> q;
    q.emplace(0,7,0);
    vis[0][7][0]=true;
    while(!q.empty()){
        auto [t,i,j]=q.front();
        q.pop();
        if(i-t>=0&&a[i-t][j]=='S')continue;
        if(t>0&&i-t+1>=0&&a[i-t+1][j]=='S')continue;
        if(t>=8){
            cout << "WIN\n";
            exit(0);
        }
        for(int di=-1;di<=1;di++){
            for(int dj=-1;dj<=1;dj++){
                int ii=i+di,jj=j+dj;
                if(ii>=0&&ii<8&&jj>=0&&jj<8&&!vis[t+1][ii][jj]){
                    vis[t+1][ii][jj]=true;
                    q.emplace(t+1,ii,jj);
                }
            }
        }
    }
    cout << "LOSE\n";
}