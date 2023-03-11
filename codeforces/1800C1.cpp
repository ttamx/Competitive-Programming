#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    reverse(a.begin(),a.end());
    int cnt=0;
    a.emplace_back(0);
    multiset<ll> ms;
    for(auto x:a){
        if(x==0){
            while(ms.size()>cnt)ms.erase(ms.begin());
            cnt++;
        }else{
            ms.emplace(x);
        }
    }
    ll ans=0;
    for(auto x:ms)ans+=x;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}