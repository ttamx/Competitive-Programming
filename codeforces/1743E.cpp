#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5005;
const ll INF=LLONG_MAX/2;

ll p[2],t[2];
int h,s;
ll dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<2;i++){
        cin >> p[i] >> t[i];
    }
    cin >> h >> s;
    for(int i=1;i<=h;i++){
        dp[i]=INF;
    }
    for(int i=0;i<h;i++){
        for(int x=0;x<2;x++){
            for(int j=1;;j++){
                ll tt=t[x]*j;
                ll dmg;
                if(tt>=t[x^1]){
                    dmg=(p[0]+p[1]-s)+(tt-t[0])/t[0]*(p[0]-s)+(tt-t[1])/t[1]*(p[1]-s);
                }else{
                    dmg=(p[x]-s)*j;
                }
                int k=min((ll)h,i+dmg);
                dp[k]=min(dp[k],dp[i]+tt);
                if(k==h)break;
            }
        }
    }
    cout << dp[h] << "\n";
}