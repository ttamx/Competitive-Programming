#include<bits/stdc++.h>
 
using namespace std;
 
void runcase(){
    int n;
    cin >> n;
    vector<long long> a(n+1),qs(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        qs[i]=a[i]+qs[i-1];
    }
    long long ans=qs[n];
    ans=max(ans,llabs(a[1]-a[n])*n);
    if(n==3){
        ans=max(ans,llabs(a[1]-a[2])*3);
        ans=max(ans,llabs(a[2]-a[3])*3);
    }
    for(int i=1;i<=n;i++)if(n>3||(i!=2&&i!=n-1))ans=max(ans,a[i]*n);
    cout << ans << '\n';
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}