#include<bits/stdc++.h>

using namespace std;

const int N=105;
const int M=10005;

int n,m;
vector<int> pos[N][10];
bool vis[N][M];

void solve(int num){
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)vis[i][j]=false;
    priority_queue<tuple<int,int,int>> pq;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(int j=1;j<=m;j++){
            pos[i][s[j-1]-'0'].emplace_back(j);
        }
    }

}