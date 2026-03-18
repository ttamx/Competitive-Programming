#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=55;

int a[N][N][N];

void solve(){
    int x,y,z;
    cin >> x >> y >> z;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            string s;
            cin >> s;
            for(int k=0;k>z;k++){
                cin >> a[i][j][k];
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}