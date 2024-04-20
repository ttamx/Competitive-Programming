#include<bits/stdc++.h>

using namespace std;

const int N=3005;

int n,p,s;
int a[N],b[N],ord[N];
int dp[N][N];
bool ok[N][N];
vector<int> ans[2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p >> s;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    iota(ord+1,ord+n+1,1);
    sort(ord+1,ord+n+1,[&](int l,int r){
        return a[l]-b[l]>a[r]-b[r];
    });
    for(int i=1;i<=n;i++){
        int k=ord[i];
        for(int j=1;j<=p+s;j++){
            dp[i][j]=dp[i-1][j];
            int val=dp[i-1][j-1]+(j<=p?a[k]:b[k]);
            if(val>dp[i][j]){
                dp[i][j]=val;
                ok[i][j]=true;
            }
        }
    }
    cout << dp[n][p+s] << "\n";
    for(int i=n,j=p+s;i>=1;i--)if(ok[i][j]){
        ans[j>p].emplace_back(ord[i]);
        j--;
    }
    for(int i=0;i<2;i++){
        sort(ans[i].begin(),ans[i].end());
        for(auto x:ans[i])cout << x << " ";
        cout << "\n";
    }
}