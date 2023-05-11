#include<bits/stdc++.h>

using namespace std;

int n;
multiset<int> ms;
long long ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        ms.emplace(x);
        ms.emplace(x);
        ans+=*ms.rbegin()-x;
        ms.erase(prev(ms.end()));
    }
    cout << ans;
}