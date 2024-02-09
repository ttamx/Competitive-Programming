#include<bits/stdc++.h>

using namespace std;

using pi = pair<int,int>;
using ppi = pair<pi,pi>;

const int N=3e5+5;
const int M=25;
const int K=(1<<20)+5;

int n,m,h;
int a[N],sum[M];
int cnt[K];
ppi dp[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            int x;
            cin >> x;
            a[i]|=x<<j;
            sum[j]+=x;
        }
        cnt[a[i]]++;
    }
    for(int i=0;i<m;i++)sum[i]-=n/2;
    for(int )
}