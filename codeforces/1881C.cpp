#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<string> v(n);
    for(auto &x:v)cin >> x;
    int ans=0;
    for(int i=0;i<n/2;i++){
        for(int j=0;j<n/2;j++){
            char res=max({v[i][j],v[j][n-i-1],v[n-i-1][n-j-1],v[n-j-1][i]});
            ans+=res*4-v[i][j]-v[j][n-i-1]-v[n-i-1][n-j-1]-v[n-j-1][i];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}