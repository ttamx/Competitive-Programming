#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int G=20;
const int N=1e5+5;
const int M=(1<<G)+5;
const ll inf=1e18;

int n,g;
int a[N];
vector<int> pos[G];
ll dp[M],pref[N],suff[N];
ll f[G][G][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed;
    string s;
    cin >> s;
    n=s.size();
    for(int i=1;i<=n;i++){
        a[i]=s[i-1]-'A';
        g=max(g,a[i]+1);
    }
    for(int i=0;i<g;i++)pos[i].emplace_back(0);
    for(int i=1;i<=n;i++)pos[a[i]].emplace_back(i);
    for(int i=0;i<g;i++){
        for(int j=0;j<g;j++){
            int add=i==j?1:2;
            int cnt=0;
            for(int k=1;k<=n;k++){
                pref[k]=pref[k-1]+(a[k]==i?cnt:0);
                cnt+=a[k]==j?add:0;
            }
            cnt=0;
            for(int k=n;k>=1;k--){
                suff[k]=suff[k+1]+(a[k]==i?cnt:0);
                cnt+=a[k]==j?add:0;
            }
            for(auto k:pos[i])f[i][j][k]=pref[k]+suff[k+1];
        }
    }
    for(int mask=1;mask<1<<g;mask++){
        dp[mask]=inf;
        for(int bit=0;bit<g;bit++){
            if(mask>>bit&1){
                int mask2=1<<bit^mask;
                int l=0,r=pos[bit].size()-1;
                while(l<r){
                    ll m=(l+r)/2;
                    int dif=0;
                    for(int i=0;i<g;i++)if(mask>>i&1)dif+=f[bit][i][pos[bit][m+1]]-f[bit][i][pos[bit][m]];
                    if(dif>=0)r=m;
                    else l=m+1;
                }
                ll res=0;
                for(int i=0;i<g;i++)if(mask>>i&1)res+=f[bit][i][pos[bit][l]];
                dp[mask]=min(dp[mask],dp[mask2]+res);
            }
        }
    }
    cout << dp[(1<<g)-1]/2.l;
}