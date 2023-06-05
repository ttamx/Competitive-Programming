#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m)),b(n,vector<int>(m));
    for(auto &v:a)for(auto &x:v)cin >> x;
    for(auto &v:b)for(auto &x:v)cin >> x;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]>b[i][j])swap(a[i][j],b[i][j]);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i&&a[i][j]<=a[i-1][j])return void(cout << "Impossible\n");
            if(j&&a[i][j]<=a[i][j-1])return void(cout << "Impossible\n");
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i&&b[i][j]<=b[i-1][j])return void(cout << "Impossible\n");
            if(j&&b[i][j]<=b[i][j-1])return void(cout << "Impossible\n");
        }
    }
    cout << "Possible\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}