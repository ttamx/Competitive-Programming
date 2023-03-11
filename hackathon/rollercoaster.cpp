#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n+2,-1e18);
    vector<pair<int,ll>> ans;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)if(a[i]>a[i-1]&&a[i]>a[i+1])ans.push_back({i-1,a[i]});
    if(ans.size()==0){
        cout << "There is no lift hill";
    }else if(ans.size()==1){
        cout << "There is 1 lift hill at index(height): " << ans[0].first << '(' << ans[0].second << ')';
    }else{
        cout << "There are " << ans.size() << " lift hills at index(height):";
        for(auto [x,y]:ans) cout <<  " " << x << '(' << y << ')';
    }
}