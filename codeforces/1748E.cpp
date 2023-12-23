#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=1e9+7;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<ll>> dp(n+2,vector<ll>(m+2,0));
    dp[0]=vector<ll>(m+2,1);
    vector<int> l(n+2),r(n+2);
    stack<int> st;
    int rt=-1;
    for(int i=1;i<=n;i++){
        while(!st.empty()&&a[st.top()]<a[i]){
            l[i]=st.top();
            st.pop();
        }
        if(st.empty())rt=i;
        else r[st.top()]=i;
        st.emplace(i);
    }
    function<void(int)> dfs=[&](int u){
        if(l[u])dfs(l[u]);
        if(r[u])dfs(r[u]);
        for(int i=1;i<=m;i++)dp[u][i]=(dp[u][i-1]+dp[l[u]][i-1]*dp[r[u]][i])%mod;;
    };
    dfs(rt);
    cout << dp[rt][m] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}