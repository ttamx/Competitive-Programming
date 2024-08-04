#include<bits/stdc++.h>
 
using namespace std;
 
const int N=1e6+5;
 
int n,m;
int dp[3][3][5],ndp[3][3][5];
string s;
tuple<int,int,int> qr[N];
bool ok[N];
 
int& norm(int &x){
    return x%=m;
}
 
int main(){
    cin >> n >> m;
    cin >> s;
    int mn=0,mx=0,cur=0,ans=1;
    for(int i=0;i<n;i++){
        if(s[i]=='P'){
            qr[n-i-1]={cur+1,mn,mx};
            ok[n-i-1]=true;
        }
        cur+=s[i]=='L'?1:-1;
        mn=min(mn,cur);
        mx=max(mx,cur);
    }
    dp[0][0][2]=1;
    for(int i=1;i<=n;i++){
        if(ok[i-1]){
            auto [val,mn2,mx2]=qr[i-1];
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    if(max(mx2,val+k)-min(mn2,val-j)<=2){
                        for(int x=0;x<5;x++){
                            norm(ans+=dp[j][k][x]);
                        }
                    }
                }
            }
        }
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int x=0;x<5;x++){
                    ndp[j][k][x]=0;
                }
            }
        }
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int x=-2;x<=2;x++){
                    if(x<2)norm(ndp[j][max(k,x+1)][x+3]+=dp[j][k][x+2]);
                    if(x>-2)norm(ndp[max(j,-x+1)][k][x+1]+=dp[j][k][x+2]);
                }
            }
        }
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int x=0;x<5;x++){
                    dp[j][k][x]=ndp[j][k][x];
                }
            }
        }
    }
    cout << ans;
}