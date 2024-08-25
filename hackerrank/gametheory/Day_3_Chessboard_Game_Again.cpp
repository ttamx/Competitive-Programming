#include<bits/stdc++.h>

using namespace std;

const int N=15;
const int INF=1e9;

int dp[N][N];
bool vis[N][N];

int nimber(int x,int y){
    if(x<0||x>=N||y<0||y>=N)return INF;
    if(vis[x][y])return dp[x][y];
    vis[x][y]=true;
    vector<int> res;
    res.emplace_back(nimber(x-2,y-1));
    res.emplace_back(nimber(x-2,y+1));
    res.emplace_back(nimber(x+1,y-2));
    res.emplace_back(nimber(x-1,y-2));
    vector<bool> seen(5);
    for(auto x:res)if(x<5)seen[x]=true;
    int mex=0;
    while(seen[mex])mex++;
    return dp[x][y]=mex;
}

void runcase(){
    int n;
    cin >> n;
    int sum=0;
    while(n--){
        int x,y;
        cin >> x >> y;
        x--,y--;
        sum^=nimber(x,y);
    }
    cout << (sum?"First":"Second") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}