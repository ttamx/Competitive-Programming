#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

vector<ll> calculate_costs(vector<int> w,vector<int> a,vector<int> b,vector<int> qr){
    int n=w.size();
    vector<ll> ans;
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return w[i]<w[j];
    });
    auto work=[&](vector<int> &a){
        vector<int> res(n);
        for(int i=0;i<n;i++){
            res[i]=a[ord[i]];
        }
        swap(a,res);
    };
    work(w);
    work(a);
    work(b);
    vector<ll> qs(n);
    for(int i=0;i<n;i++){
        qs[i]=a[i];
    }
    for(int i=1;i<n;i++){
        qs[i]+=qs[i-1];
    }
    for(auto d:qr){
        vector<ll> dp(n+1,INF);
        dp[0]=0;
        deque<int> dq;
        auto calc=[&](int i){
            return -qs[i]+dp[i]+b[i];
        };
        for(int i=0;i<n;i++){
            dp[i+1]=min(dp[i+1],dp[i]+a[i]);
            while(!dq.empty()&&w[i]-w[dq.front()]>d){
                dq.pop_front();
            }
            if(!dq.empty()){
                dp[i+1]=min(dp[i+1],b[i]+qs[i-1]+calc(dq.front()));
            }
            while(!dq.empty()&&calc(dq.back())>=calc(i)){
                dq.pop_back();
            }
            dq.emplace_back(i);
        }
        ans.emplace_back(dp[n]);
    }
    return ans;
}
