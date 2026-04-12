#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int INF=1e9;

int n;
int a[N];
int dp[N][N];
tuple<int,int,int,int> par[N][N];

bool update(int &x,int val){
    if(val>=x)return false;
    x=val;
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    if(n==1){
        cout << a[1] << "\n";
        cout << 1 << "\n";
        exit(0);
    }
    for(int i=1;i<=n+2;i++){
        for(int j=1;j<=n+2;j++){
            dp[i][j]=INF;
        }
    }
    dp[1][2]=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(update(dp[i][j+2],dp[i][j]+max(a[j],a[j+1]))){
                par[i][j+2]=make_tuple(i,j,j,j+1);
            }
            if(update(dp[j][j+2],dp[i][j]+max(a[i],a[j+1]))){
                par[j][j+2]=make_tuple(i,j,i,j+1);
            }
            if(update(dp[j+1][j+2],dp[i][j]+max(a[i],a[j]))){
                par[j+1][j+2]=make_tuple(i,j,i,j);
            }
        }
    }
    if(n%2==1){
        int st=-1,best=INF;
        for(int i=1;i<=n;i++){
            if(update(best,dp[i][n+1]+a[i])){
                st=i;
            }
        }
        cout << best << "\n";
        vector<pair<int,int>> ans;
        for(int i=st,j=n+1;j>2;){
            auto [ii,jj,x,y]=par[i][j];
            ans.emplace_back(x,y);
            i=ii,j=jj;
        }
        reverse(ans.begin(),ans.end());
        for(auto [x,y]:ans){
            cout << x << " " << y << "\n";
        }
        cout << st << "\n";
    }else{
        int st=-1,best=INF;
        for(int i=1;i<=n;i++){
            if(update(best,dp[i][n]+max(a[i],a[n]))){
                st=i;
            }
        }
        cout << best << "\n";
        vector<pair<int,int>> ans;
        ans.emplace_back(st,n);
        for(int i=st,j=n;j>2;){
            auto [ii,jj,x,y]=par[i][j];
            ans.emplace_back(x,y);
            i=ii,j=jj;
        }
        reverse(ans.begin(),ans.end());
        for(auto [x,y]:ans){
            cout << x << " " << y << "\n";
        }
    }
}