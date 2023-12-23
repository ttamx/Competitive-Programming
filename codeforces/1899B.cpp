#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<long long> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i],a[i]+=a[i-1];
    long long ans=0;
    for(int l=1;l<n;l++)if(n%l==0){
        long long mn=1e18,mx=-1e18;
        for(int i=l;i<=n;i+=l){
            long long res=a[i]-a[i-l];
            mn=min(mn,res);
            mx=max(mx,res);
        }
        ans=max(ans,mx-mn);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}