#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int mx=-2e9;
    for(auto &x:a){
        int y;
        cin >> y;
        x-=y;
        mx=max(mx,x);
    }
    vector<int> ans;
    for(int i=0;i<n;i++)if(a[i]>=mx)ans.emplace_back(i+1);
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}