#include<bits/stdc++.h>

using namespace std;

using pi = pair<int,int>;
using ppi = pair<pi,pi>;

const int N=3e5+5;
const int M=25;
const int K=(1<<20)+5;

int n,m;
int a[N],cnt[M];
ppi dp[K];

void upd(ppi &x,pi v){
    if(v.second==x.first.second)return void(x.first=min(x.first,v));
    x.second=min(x.second,v);
    if(x.first>x.second)swap(x.first,x.second);
}

void upd(ppi &x,ppi y){
    upd(x,y.first);
    upd(x,y.second);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            int x;
            cin >> x;
            a[i]|=x<<j;
            cnt[j]+=x;
        }
    }
    for(int i=0;i<1<<m;i++)dp[i]=ppi(pi(m,0),pi(m,0));
    for(int i=1;i<=n;i++)upd(dp[a[i]],pi(0,i));
    for(int k=1;k<1<<m;k<<=1){
        for(int i=0;i<1<<m;i+=k<<1){
            for(int j=0;j<k;j++){
                int u=i+j,v=i+j+k;
                auto du=dp[u],dv=dp[v];
                dp[v].first.first++;
                dp[v].second.first++;
                upd(dp[u],dv);
                upd(dp[v],du);
            }
        }
    }
    for(int i=1;i<=n;i++){
        int mask=0,ans=0;
        for(int j=0;j<m;j++){
            int res=cnt[j]-(a[i]>>j&1);
            if(res==n/2)mask|=1<<j;
            if(res>=n/2)ans++;
        }
        cout << ans-(dp[mask].first.second!=i?dp[mask].first:dp[mask].second).first << "\n";
    }
}