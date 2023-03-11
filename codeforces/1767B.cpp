#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int ans;
    cin >> ans;
    vector<int> a(n-1);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    for(auto x:a){
        if(x<=ans)continue;
        ans=(ans+x+1)/2;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}