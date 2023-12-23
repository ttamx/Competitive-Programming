#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    long long sum=0,ans=0;
    for(int i=n;i>=1;i--){
        if(sum>0)ans+=sum;
        sum+=a[i];
    }
    ans+=sum;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}