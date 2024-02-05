#include<bits/stdc++.h>

using namespace std;

const int N=505;

int r,c,m;
string s;
bitset<N> a[N],dp[N],ndp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> r >> c >> m;
    for(int i=1;i<=r;i++){
        for(int j=0;j<c;j++){
            char x;
            cin >> x;
            a[i][j]=x=='.';
        }
        dp[i]=a[i];
    }
    cin >> s;
    for(auto x:s){
        for(int i=1;i<=r;i++){
            if(x=='E')ndp[i]=dp[i]<<1;
            if(x=='W')ndp[i]=dp[i]>>1;
            if(x=='N')ndp[i]=dp[i+1];
            if(x=='S')ndp[i]=dp[i-1];
            if(x=='?')ndp[i]=(dp[i]<<1)|(dp[i]>>1)|dp[i+1]|dp[i-1];
        }
        for(int i=1;i<=r;i++)dp[i]=ndp[i]&a[i];
    }
    int ans=0;
    for(int i=1;i<=r;i++)ans+=dp[i].count();
    cout << ans;
}