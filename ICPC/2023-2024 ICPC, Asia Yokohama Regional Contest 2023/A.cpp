#include<bits/stdc++.h>

using namespace std;

int n,m;
string a[10];
int ans=0;
string s="YOKOHAMA";

void solve(int i,int j,int c){
    if(i<0||i>=n||j<0||j>=m||a[i][j]!=s[c])return;
    if(c==7){
        ans++;
        return;
    }
    solve(i-1,j,c+1);
    solve(i+1,j,c+1);
    solve(i,j-1,c+1);
    solve(i,j+1,c+1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            solve(i,j,0);
        }
    }
    cout << ans;
}