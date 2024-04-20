#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &[x,e]:a)cin >> x >> e;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    n=a.size();
    vector<int> ok(n,1);
    for(int t=0;t<2;t++){
        set<int> s;
        for(int i=0;i<n;i++){
            auto [x,e]=a[i];
            int val=e+(t?-x:x);
            if(s.lower_bound(val)!=s.end())ok[i]=0;
            s.emplace(val);
        }
        reverse(a.begin(),a.end());
        reverse(ok.begin(),ok.end());
    }
    cout << accumulate(ok.begin(),ok.end(),0);
}