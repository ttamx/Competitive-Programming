#include<bits/stdc++.h>

using namespace std;

int n,cnt;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    long long ans=0;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        if(x)cnt++;
        else ans+=cnt;
    }
    cout << ans;
}