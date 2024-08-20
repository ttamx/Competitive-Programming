#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2505;

int n;
string s;
ll a,b,c;
int nxt[N][N];
ll dp[N][N];

vector<int> z_algo(const string &s){
    int n=s.size();
    vector<int> z(n);
    z[0]=n;
    for(int i=1,l=0,r=1;i<n;i++){
        if(i<r)z[i]=min(r-i,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    return z;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cin >> s;
    cin >> a >> b >> c;
    for(int l=0;l<n;l++){
        auto z=z_algo(s.substr(l,n-l));
        int p=l;
        for(int r=l;r<n;r++){
            while(p<n&&(p<=r||z[p-l]<r-l+1))p++;
            nxt[l][r]=p;
        }
    }
    for(int l=0;l<n;l++){
        for(int r=l;r<n;r++){
            dp[l][r]=(r-l+1)*a;
        }
    }
    for(int sz=1;sz<=n;sz++){
        for(int l=0,r=sz-1;r<n;l++,r++){
            if(l>0)dp[l-1][r]=min(dp[l-1][r],dp[l][r]+a);
            if(r+1<n)dp[l][r+1]=min(dp[l][r+1],dp[l][r]+a);
            int p=nxt[l][r];
            int cnt=2;
            while(p<n){
                dp[l][p+sz-1]=min(dp[l][p+sz-1],dp[l][r]+(p+sz-l-sz*cnt)*a+b+cnt*c);
                p=nxt[p][p+sz-1];
                cnt++;
            }
        }
    }
    cout << dp[0][n-1] << "\n";
}