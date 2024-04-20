#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int K=105;

struct Info{
    ll h,val,mn;
    Info(ll _h,ll _val,ll _mn):h(_h),val(_val),mn(_mn){}
};

int n,k;
ll a[N];
vector<ll> dp(N);

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        dp[i]=max(dp[i-1],a[i]);
    }
    for(int j=2;j<=k;j++){
        stack<Info> s;
        vector<ll> new_dp(N);
        for(int i=j;i<=n;i++){
            ll tmp=dp[i-1]+a[i];
            Info res(a[i],tmp,tmp);
            while(!s.empty()&&a[i]>=s.top().h){
                Info top=s.top();
                s.pop();
                top.val+=a[i]-top.h;
                res.val=min(res.val,top.val);
                res.mn=min(res.mn,top.val);
            }
            if(!s.empty())res.mn=min(res.mn,s.top().mn);
            s.emplace(res);
            new_dp[i]=res.mn;
        }
        swap(dp,new_dp);
    }
    cout << dp[n];
}