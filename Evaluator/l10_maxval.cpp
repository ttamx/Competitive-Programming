#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,k;
int qs[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;++i){
        cin >> qs[i];
        qs[i]+=qs[i-1];
    }
    int ans=-2e9;
    for(int i=k;i<=n;++i){
        ans=max(ans,qs[i]-qs[i-k]);
    }
    cout << ans;
}