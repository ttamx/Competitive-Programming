#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int si=-1,sj=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='.'){
                si=i,sj=j;
            }
        }
    }
    vector<vector<bool>> vis(n,vector<bool>(m));
    vector<pair<int,int>> q;
    auto go=[&](int i,int j){
        if(i<0||j<0||i>=n||j>=m||vis[i][j]||a[i][j]!='.')return;
        q.emplace_back(i,j);
        vis[i][j]=true;
    };
    go(si,sj)
;        for(int t=0;t<q.size();t++){
        auto [i,j]=q[t];
        go(i-1,j);
        go(i,j-1);
        go(i,j+1);
        go(i+1,j);
    }
    assert(q.size()>=k);
    for(int t=0;t<k;t++){
        auto [i,j]=q.back();
        q.pop_back();
        a[i][j]='X';
    }
    for(auto x:a){
        cout << x << "\n";
    }
}