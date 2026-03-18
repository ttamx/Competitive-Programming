#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<pair<int,int>> a(k);
    vector<vector<int>> mark(n+1,vector<int>(m+1));
    for(auto &[x,y]:a){
        cin >> x >> y;
        mark[x][y]=1;
    }
    auto check=[&](int mid){
        vector<vector<int>> b(n+1,vector<int>(m+1));
        for(auto [x,y]:a){
            b[x][y]++;
            if(x+mid<=n)b[x+mid][y]--;
            if(y+mid<=m)b[x][y+mid]--;
            if(x+mid<=n&&y+mid<=m)b[x+mid][y+mid]++;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
            }
        }
        vector<vector<int>> c(n+1,vector<int>(m+1));
        queue<pair<int,int>> q;
        auto push=[&](int i,int j){
            if(i>=mid&&i<=n&&j>=mid&&j<=m&&!b[i][j]&&!c[i][j]){
                c[i][j]=1;
                q.emplace(i,j);
            }
        };
        for(int i=mid;i<=n;i++){
            for(int j=mid;j<=m;j++){
                if(!b[i][j]){
                    push(i,j);
                    break;
                }
            }
            if(!q.empty())break;
        }
        while(!q.empty()){
            auto [i,j]=q.front();
            q.pop();
            push(i-1,j);
            push(i,j-1);
            push(i,j+1);
            push(i+1,j);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!mark[i][j]){
                    int x=min(i+mid-1,n);
                    int y=min(j+mid-1,m);
                    if(c[x][y]-c[x][j-1]-c[i-1][y]+c[i-1][j-1]==0){
                        return false;
                    }
                }
            }
        }
        return true;
    };
    int l=0,r=min(n,m);
    while(l<r){
        int mid=(l+r+1)/2;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    cout << (l?l:-1) << "\n";
}