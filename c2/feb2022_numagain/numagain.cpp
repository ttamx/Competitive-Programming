#include "numagain.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2005;
const int M=1e6+5;
const int mod=1e9+7;

struct mint{
    ll x;
    mint():x(0){}
    mint(ll _x):x(_x%mod){}
    friend mint operator+(mint a,mint b){return mint(a.x+b.x);}
    friend mint operator-(mint a,mint b){return mint(mod+a.x-b.x);}
    friend mint operator*(mint a,mint b){return mint(a.x*b.x);}
};

ll cnt[N];
mint dp[N][N],dp2[N][N],pw2[M],ans;

int find_ans(vector<int>number)
{
    pw2[0]=1;
    for(int i=1;i<=number.size();i++)pw2[i]=pw2[i-1]*2;
    for(auto x:number)cnt[x]++;
    for(int i=0;i<=2000;i++)dp2[i+1][i]=2;
    for(int i=1;i<=2000;i++)dp[i][i]=pw2[cnt[i]],dp2[i][i]=3*pw2[cnt[i]]-1;
    for(int sz=2;sz<=2000;sz++){
        for(int l=1,r=sz;r<=2000;l++,r++){
            dp[l][r]=dp[l][r-1]*pw2[cnt[r]];
            dp2[l][r]=((dp2[l][r-1]+dp[l][r-1])*(pw2[cnt[r]]-1))+dp2[l][r-1];
        }
    }
    for(int l=1;l<=2000;l++){
        for(int r=l+1;r<=2000;r++){
            ans=ans+((dp2[l+1][r-1])*(pw2[cnt[l]]-1)*(pw2[cnt[r]]-1)*(r-l));
        }
    }
    return ans.x;
}
