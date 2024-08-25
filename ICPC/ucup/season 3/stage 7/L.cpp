#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<long long> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]+=a[i-1];
    }
    int ans=0;
    for(int s=1;s<=n;s++){
        for(int i=s;i<=n;i++){
            long long sum=a[i]-a[i-s];
            if(sum==1LL*s*s){
                ans++;
            }
            i+=abs(sum-1LL*s*s)/n;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}