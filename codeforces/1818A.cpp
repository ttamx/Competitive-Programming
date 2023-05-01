#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<string> v(n);
    for(auto &x:v)cin >> x;
    vector<bool> b(n,true),d(k);
    int ans=n;
    for(int i=1;i<n;i++){
        bool ok=false;
        for(int j=0;j<k;j++)ok|=(v[i][j]!=v[0][j]);
        ans-=ok;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}