#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(int i=0;i<n;i++)cin >> a[i].first,a[i].second=i;
    vector<int> ans(n);
    sort(a.rbegin(),a.rend());
    for(int i=0;i<n;i++)ans[a[i].second]=i+1;
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}