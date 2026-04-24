#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    set<int> s;
    int mx=0;
    for(auto x:a){
        mx=max(mx,x);
        if(mx==x)s.emplace(x);
    }
    int mn=1e9;
    reverse(a.begin(),a.end());
    vector<int> ans;
    for(auto x:a){
        mn=min(mn,x);
        if(mn==x&&s.count(x))ans.emplace_back(x);
    }
    reverse(ans.begin(),ans.end());
    cout << ans.size() << " ";
    if(ans.size()>100)ans.resize(100);
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}