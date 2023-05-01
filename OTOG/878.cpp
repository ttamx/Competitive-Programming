#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    vector<vector<int>> c(n,vector<int>(n));
    for(auto &v:c)for(auto &x:v)cin >> x,x=x&1^1;
    auto sol=[&](){
        for(int i=0;i<n;i++)b[i]=a[i]^c[i][i];
    };
    auto chk=[&](){
        int res=0;
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)res+=(a[i]^b[j]!=c[i][j]);
        return res;
    };
    int ans=2e9;
    for(int i=0;i<1<<n;i++){
        for(int j=0;j<n;j++)a[j]=(i>>j)&1;
        sol();
        int cnt=chk();
        int sa=0,sb=0;
        for(auto x:a)sa+=x;
        for(auto x:b)sb+=x;
        if((sa^sb)&1)continue;
        if(sa<sb)swap(sa,sb);
        if(sa!=cnt)continue;
        ans=min(ans,sa);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}