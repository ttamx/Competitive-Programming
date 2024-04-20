#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int dp[N][30];
string t,ans;
stack<char> s;

void solve(int l,int r){
    if(l>r)return;
    int m=dp[r][t[l]];
    ans[m]=')';
    solve(l+1,m-1);
    solve(m+1,r);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    for(auto &x:t){
        if(!s.empty()&&x==s.top())s.pop();
        else s.emplace(x);
        x-='a';
    }
    if(!s.empty())cout << -1,exit(0);
    n=t.size();
    ans.assign(n,'(');
    for(int i=1;i<n;i++){
        int p=dp[i-1][t[i]]-1;
        if(p>0)for(int j=0;j<26;j++){
            dp[i][j]=t[p]==j?p:dp[p][j];
        }
        dp[i][t[i]]=i;
    }
    solve(0,n-1);
    cout << ans;
}