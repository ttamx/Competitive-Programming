#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k,p;
    cin >> n >> p >> k;
    long long ans=0;
    map<int,int> cnt;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        ans+=cnt[(1LL*x*x%p*x%p*x%p+p-1LL*k*x%p)%p]++;
    }
    cout << ans << "\n";
}