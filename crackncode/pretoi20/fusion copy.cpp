#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int M=1e6+5;

int n,q;
int a[N],cnt[2*M],sum;
bitset<M> dp;
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        cnt[a[i]]++;
        sum+=a[i];
        ans-=1LL*a[i]*(a[i]-1);
    }
    ans+=1LL*sum*(sum-1);
    ans/=2;
    if(q){
        dp[0]=1;
        for(int i=1;i<M;i++){
            if(cnt[i]>2){
                cnt[i*2]+=(cnt[i]-1)/2;
                cnt[i]-=(cnt[i]-1)/2*2;
            }
            while(cnt[i]--)dp|=dp<<i;
        }
        for(int i=sum/2;i>=0;i--)if(dp[i]){
            ans-=1LL*i*(sum-i);
            break;
        }
    }
    cout << ans;
}