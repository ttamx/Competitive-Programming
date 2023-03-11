#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    int ans=0,res=0;
    int cnt1[30]={},cnt2[30]={};
    for(auto x:s)if(++cnt2[x-'a']==1)res++;
    for(int i=0;i<n-1;i++){
        if(--cnt2[s[i]-'a']==0)res--;
        if(++cnt1[s[i]-'a']==1)res++;
        ans=max(ans,res);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}