#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

const int G=20;
const int N=1e5+5;
const int M=(1<<G)+5;

int n,g;
int a[N];
vector<int> pos[G];
ld dp[M],pref[N],suff[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed;
    string s;
    cin >> s;
    n=s.size();
    for(int i=1;i<=n;i++){
        a[i]=s[i-1]-'A';
        pos[a[i]].emplace_back(i);
        g=max(g,a[i]+1);
    }
    for(int mask=1;mask<1<<g;mask++){
        dp[mask]=DBL_MAX;
        for(int bit=0;bit<g;bit++){
            if(mask>>bit&1){
                int mask2=1<<bit^mask;
                ld cnt=0;
                for(int i=1;i<=n;i++){
                    cnt+=mask2>>a[i]&1;
                    pref[i]=pref[i-1];
                    if(a[i]==bit)pref[i]+=cnt,cnt+=0.5l;
                }
                cnt=0;
                for(int i=n;i>=1;i--){
                    cnt+=mask2>>a[i]&1;
                    suff[i]=suff[i+1];
                    if(a[i]==bit)suff[i]+=cnt,cnt+=0.5l;
                }
                ld res=LDBL_MAX;
                for(int i=0;i<=n;i++)res=min(res,pref[i]+suff[i+1]);
                dp[mask]=min(dp[mask],dp[mask2]+res);
            }
        }
    }
    cout << dp[(1<<g)-1];
}