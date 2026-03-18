#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    int c1=0,c2=0;
    for(auto &x:a){
        cin >> x;
        if(x==(x&-x)){
            c2++;
        }else if(x%2==1){
            c1++;
        }
    }
    if(c1==n||c2==n){
        cout << 0 << "\n";
        return;
    }
    auto cost=[&](int x){
        return x!=(x&-x);
    };
    int ans=1e9;
    int tot=0;
    for(auto x:a)tot+=cost(x);
    for(auto x:a){
        int cur=tot-cost(x);
        if(x%2==0)cur++;
        ans=min(ans,cur);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}