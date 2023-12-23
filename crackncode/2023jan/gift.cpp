#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> h(n+2);
    vector<ll> w(n+2),dp(n+2);
    deque<int> dq;
    multiset<ll> ms;
    for(int i=1;i<=n;i++)cin >> w[i];
    for(int i=1;i<=n;i++)cin >> h[i];
    for(int i=1;i<=n;i++)w[i]+=w[i-1];
    dq.emplace_back(0);
    for(int i=1;i<=n;i++){
        while(dq.size()>1&&h[dq.back()]<=h[i]){
            ms.erase(ms.find(h[dq.back()]+dp[dq.end()[-2]]));
            dq.pop_back();
        }
        ms.emplace(dp[dq.back()]+h[i]);
        dq.emplace_back(i);
        while(dq.size()>1&&w[i]-w[dq[0]]>m){
            int pos=dq[0];
            dq.pop_front();
            ms.erase(ms.find(h[dq[0]]+dp[pos]));
            if(dq[0]>pos+1){
                ms.emplace(h[dq[0]]+dp[pos+1]);
                dq.emplace_front(pos+1);
            }
        }
        dp[i]=*ms.begin();
    }
    cout << dp[n] << "\n";
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}