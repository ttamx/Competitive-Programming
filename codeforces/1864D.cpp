#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<string> s(n);
    for(auto &x:s)cin >> x;
    vector<vector<int>> a(n,vector<int>(n)),b(n,vector<int>(n)),c(n,vector<int>(n));
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int num=s[i][j]-'0';
            c[i][j]^=a[i][j]^b[i][j];
            num^=c[i][j];
            if(num>0){
                a[i][j]^=1;
                b[i][j]^=1;
                c[i][j]^=1;
                ans++;
            }
            if(i<n-1){
                if(j>0)a[i+1][j-1]^=a[i][j];
                if(j<n-1)b[i+1][j+1]^=b[i][j];
                c[i+1][j]^=c[i][j];
            }
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