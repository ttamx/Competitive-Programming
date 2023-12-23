#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<pair<int,int>> a(n);
    vector<int> b(n);
    for(int i=0;i<n;i++){
        cin >> a[i].first;
        a[i].second=i;
    }
    for(auto &x:b)cin >> x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    vector<int> ans(n),ans2(n);
    for(int i=0;i<n;i++)ans[(n-k+i)%n]=b[i];
    int cnt=0;
    for(int i=0;i<n;i++)cnt+=a[i].first>ans[i];
    if(cnt!=k)return void(cout << "NO\n");
    for(int i=0;i<n;i++)ans2[a[i].second]=ans[i];
    cout << "YES\n";
    for(auto x:ans2)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}