#include<bits/stdc++.h>

using namespace std;

int n,m,k;
vector<string> a[105];
vector<pair<int,int>> cnt;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=k+1;i++){
        a[i].resize(n);
        for(auto &s:a[i])cin >> s;
        int tmp=0;
        for(int x=1;x<n-1;x++)for(int y=1;y<m-1;y++)if(a[i][x][y]!=a[i][x-1][y]&&a[i][x][y]!=a[i][x][y-1]&&a[i][x][y]!=a[i][x+1][y]&&a[i][x][y]!=a[i][x][y+1])tmp++;
        cnt.push_back({tmp,i});
    }
    sort(cnt.rbegin(),cnt.rend());
    vector<tuple<int,int,int>> ans;
    vector<string> cur=a[cnt[0].second];
    for(int u=1;u<=k;u++){
        int i=cnt[u].second;
        for(int x=1;x<n-1;x++)for(int y=1;y<m-1;y++)if(a[i][x][y]!=cur[x][y]){
            cur[x][y]=a[i][x][y];
            ans.push_back({1,x+1,y+1});
        }
        ans.push_back({2,i,0});
    }
    cout << cnt[0].second << '\n';
    cout << ans.size() << '\n';
    for(auto [x,y,z]:ans){
        if(x==1)cout << x << ' ' << y << ' ' << z << '\n';
        else cout << x << ' ' << y << '\n';
    }
}