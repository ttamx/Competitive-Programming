#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

void runcase(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    s=" "+s;
    vector<ll> dp1(n+1),dp2(n+1);
    deque<int> dq1,dq2;
    dq1.emplace_back(0);
    for(int i=1;i<=n;i++){
        dp1[i]=dp1[i-1]+i;
        dp2[i]=INF;
        while(!dq1.empty()&&i-dq1.front()>k+1)dq1.pop_front();
        while(!dq2.empty()&&i-dq2.front()>k)dq2.pop_front();
        if(s[i]=='1'&&!dq1.empty())dp2[i]=min(dp2[i],dp1[dq1.front()]+i);
        if(!dq2.empty())dp1[i]=min(dp1[i],dp2[dq2.front()]);
        dp1[i]=min(dp1[i],dp2[i]);
        while(!dq1.empty()&&dp1[dq1.back()]>=dp1[i])dq1.pop_back();
        dq1.emplace_back(i);
        while(!dq2.empty()&&dp2[dq2.back()]>=dp2[i])dq2.pop_back();
        dq2.emplace_back(i);
    }
    cout << dp1[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}