#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=32;

int cnt[N],pre[N];
mint dp[N],dp2[N];

void runcase(){
    int n,k;
    cin >> n >> k;
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        pq.emplace(x);
    }
    mint ans=1;
    while(k>0&&!pq.empty()){
        int x=pq.top();
        pq.pop();
        k--;
        ans*=x;
        for(int i=min(x,N)-1;i>=1;i--){
            if(k>=pre[i]){
                k-=pre[i];
                ans*=dp2[i];
                break;
            }else{
                pq.emplace(i);
            }
        }
    }
    assert(k==0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[1]=dp2[1]=1;
    cnt[1]=pre[1]=1;
    for(int i=2;i<N;i++){
        cnt[i]=pre[i-1]+1;
        dp[i]=dp2[i-1]*i;
        pre[i]=pre[i-1]+cnt[i];
        dp2[i]=dp2[i-1]*dp[i];
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}