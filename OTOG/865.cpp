#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1005;
const int K=1e5+2005;

int n,m,k,q;
ll all[K];
ll cnt;
bool vis[N][N];
vector<pair<int,int>> v;

bool valid(int x,int y){
    return 1<=x&&x<=n&&1<=y&&y<=m;
}

void go(int x,int y,int i){
    if(valid(x,y)&&!vis[x][y]){
        cnt++;
        vis[x][y]=true;
        all[i]++;
        v.emplace_back(x,y);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k >> q;
    for(int i=1;i<=k;i++){
        all[i]=all[i-1]+cnt;
        auto res=v;
        v.clear();
        for(auto [x,y]:res){
            go(x+1,y,i);
            go(x-1,y,i);
            go(x,y+1,i);
            go(x,y-1,i);
        }
        int x,y;
        cin >> x >> y;
        x++,y++;
        all[i]++;
        if(!vis[x][y]){
            cnt++;
            vis[x][y]=true;
            v.emplace_back(x,y);
        }
    }
    for(int i=k+1;i<=k+n+m;i++){
        all[i]=all[i-1]+cnt;
        auto res=v;
        v.clear();
        for(auto [x,y]:res){
            go(x+1,y,i);
            go(x-1,y,i);
            go(x,y+1,i);
            go(x,y-1,i);
        }
    }
    while(q--){
        int x;
        cin >> x;
        if(x<=k+n+m){
            cout << all[x] << '\n';
        }else{
            cout << all[k+n+m]+(x-k-n-m)*cnt << '\n';
        }
    }
}