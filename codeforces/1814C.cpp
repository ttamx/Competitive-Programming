#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    ll s1,s2;
    cin >> n >> s1 >> s2;
    vector<pair<ll,int>> v,e(n);
    for(int i=0;i<n;i++){
        cin >> e[i].first;
        e[i].second=i+1;
    }
    for(int i=1;i<=n;i++){
        v.emplace_back(s1*i,0);
        v.emplace_back(s2*i,1);
    }
    vector<int> ans[2];
    sort(v.begin(),v.end());
    sort(e.rbegin(),e.rend());
    for(int i=0;i<n;i++)ans[v[i].second].emplace_back(e[i].second);
    for(int i=0;i<2;i++){
        cout << ans[i].size() << ' ';
        for(auto x:ans[i])cout << x << ' ';
        cout << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}