#include<bits/stdc++.h>

using namespace std;

const int A=1e6+5;

int cnt[A];

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x,cnt[x]++;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    long long ans=0;
    for(auto x:a)ans+=1ll*(cnt[x]-2)*(cnt[x]-1)*cnt[x];
    for(int i=2;i<=1000;i++)for(auto x:a)if(x%i==0&&x*i<A)ans+=1ll*cnt[x/i]*cnt[x]*cnt[x*i];
    for(auto x:a)cnt[x]=0;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}