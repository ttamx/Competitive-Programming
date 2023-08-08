#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int Q=5e5+5;
const int M=5005;
const int T=1005;

int n,q;
bool vis[M][M];
int ans[T];
vector<pair<int,int>> b;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        x+=2500,y+=2500;
        vis[x][y]=true;
        ans[0]++;
        b.emplace_back(x,y);
    }
    for(int t=0;t<T-1;t++){
        vector<pair<int,int>> tmp;
        for(auto [x,y]:b){
            if(!vis[x-1][y]){
                vis[x-1][y]=true;
                tmp.emplace_back(x-1,y);
                ans[t+1]++;
            }
            if(!vis[x+1][y]){
                vis[x+1][y]=true;
                tmp.emplace_back(x+1,y);
                ans[t+1]++;
            }
            if(!vis[x][y-1]){
                vis[x][y-1]=true;
                tmp.emplace_back(x,y-1);
                ans[t+1]++;
            }
            if(!vis[x][y+1]){
                vis[x][y+1]=true;
                tmp.emplace_back(x,y+1);
                ans[t+1]++;
            }
        }
        swap(b,tmp);
    }
    while(q--){
        int t;
        cin >> t;
        cout << ans[t] << "\n";
    }
}