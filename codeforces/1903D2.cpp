#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1<<20;
const int M=20;

int n,q;
int a[N];
ll tot;
ll sum[M][N];
ll sum2[M][N];
ll cnt[N];
ll ans[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    tot=N-1;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        cnt[x]++;
        tot&=x;
    }
    for(int i=0;i<N;i++){
        int pre=0;
        for(int j=19;j>=0;j--){
            if((i>>j&1)==0){
                sum[j][pre]+=cnt[i]*(i%(1<<j));
                sum2[j][pre]+=cnt[i];
            }else{
                pre|=1<<j;
            }
        }
    }
    for(int k=0;k<20;k++){
        for(int j=19;j>k;j--){
            for(int i=N-1;i>=0;i--)if((i>>j&1)==0){
                sum[k][i]+=sum[k][i^(1<<j)];
                sum2[k][i]+=sum2[k][i^(1<<j)];
            }
        }
    }
    for(int i=0;i<N;i++){
        int pre=0;
        for(int j=19;j>=0;j--){
            if(i>>j&1){
                ans[i]+=sum2[j][pre]*ll(i%(2<<j))-sum[j][pre];
                pre|=1<<j;
            }
        }
    }
    ans[tot]=0;
    for(int i=N-2;i>=0;i--)ans[i]=min(ans[i],ans[i+1]);
    while(q--){
        ll x;
        cin >> x;
        if(x>ans[N-1]){
            cout << N-1+ll(x-ans[N-1])/n << "\n";
        }else{
            cout << upper_bound(ans+tot,ans+N,x)-ans-1 << "\n";
        }
    }
}