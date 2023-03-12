#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int h,w;
    cin >> h >> w;
    vector<vector<int>> a(h,vector<int>(w));
    for(auto &v:a)for(auto &x:v)cin >> x;
    queue<tuple<int,int,map<int,bool>>> q;
    int ans=0;
    q.push({0,0,{}});
    while(!q.empty()){
        auto [i,j,mp]=q.front();
        q.pop();
        if(i==h-1&&j==w-1){
            ans++;
            continue;
        }
        mp[a[i][j]]=true;
        if(i+1<h&&!mp[a[i+1][j]])q.emplace(i+1,j,mp);
        if(j+1<w&&!mp[a[i][j+1]])q.emplace(i,j+1,mp);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}