#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MxN = 110;

int dp[MxN][MxN][MxN], n;
char a[4][MxN];
int mid;
int t[4];

int search_pos(int y) {
    int l = 0, r = n;
    while(l < r) {
        int md = (l + r) >> 1;
        if(md * md >= mid - y * y) {
            r = md;
        }
        else {
            l = md + 1;
        }
    }
    return l;
}

int DP(int i, int j, int k) {
    if(i < 0 || j < 0 || k < 0) return -100000;
    if(i == 0 && j == 0 && k == 0) return 0;
    if(dp[i][j][k] != -1) {
        return dp[i][j][k];
    }
    dp[i][j][k] = max({DP(i - 1, j, k),  DP(i, j - 1, k), DP(i, j, k - 1)});
    if(i > 0 && a[1][i] == '.') {
        dp[i][j][k] = max(dp[i][j][k], 1 + DP(min(i,max(0,i-t[0])), min(j,max(0,i-t[1])), min(k,max(0,i-t[2]))));
    }
    if(j > 0 && a[2][j] == '.') {
        dp[i][j][k] = max(dp[i][j][k], 1 + DP(min(i,max(0,j-t[1])), min(j,max(0,j-t[0])), min(k,max(0,j-t[1]))));
    }
    if(k > 0 && a[3][k] == '.') {
        dp[i][j][k] = max(dp[i][j][k], 1 + DP(min(i,max(0,k-t[2])), min(j,max(0,k-t[1])), min(k,max(0,k-t[0]))));
    }
    return dp[i][j][k];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k, cnt = 0;
    cin >> n >> k;
    for(int i=1; i<=3; ++i) {
        for(int j=1; j<=n; ++j) {
            cin >> a[i][j];
            cnt += (a[i][j] == '.');
        }
    }
    if(cnt < k) {
        cout << "-1";
        return 0;
    }
    int l = 1, r = 20000;
    while(l < r) {
        mid = (l + r + 1) >> 1;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                for(int k=0;k<=n;k++){
                    dp[i][j][k]=-1;
                }
            }
        }
        for(int i=0;i<3;i++){
            t[i]=search_pos(i);
        }
        if(DP(n, n, n) >= k) {
            l = mid;
        }
        else {
            r = mid - 1;
        }
    }
    cout << fixed << setprecision(7) << sqrt(l) << "\n";
}