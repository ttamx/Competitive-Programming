#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int mn=*min_element(a.begin(),a.end());
    int mx=*max_element(a.begin(),a.end());
    int d=mx-mn;
    int ans=0;
    while((1<<ans)<=d)ans++;
    cout << ans << "\n";
    if(ans>0&&ans<=n){
        int x=1<<ans;
        cout << x-mn%x << " ";
        for(int i=2;i<=ans;i++)cout << "0 ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}