#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k,K;
    cin >> n >> K;
    bool ans=false;
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &v:a)for(auto &x:v)cin >> x;
    k=K;
    for(int i=0;i*2+1<n;i++){
        for(int j=0;j<n;j++){
            if(a[i][j]!=a[n-i-1][n-j-1]){
                k--;
            }
        }
    }
    if(n%2==1){
        for(int i=0;i*2<n;i++){
            if(a[n/2][i]!=a[n/2][n-i-1])k--;
        }
    }
    ans|=(k>=0&&k%2==0);
    k=K;
    for(int j=0;j*2+1<n;j++){
        for(int i=0;i<n;i++){
            if(a[i][j]!=a[n-i-1][n-j-1]){
                k--;
            }
        }
    }
    if(n%2==1){
        for(int i=0;i*2<n;i++){
            if(a[i][n/2]!=a[n-i-1][n/2])k--;
        }
    }
    ans|=(k>=0&&k%2==0);
    if(k<0||k%2==1)cout << "NO\n";
    else cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}