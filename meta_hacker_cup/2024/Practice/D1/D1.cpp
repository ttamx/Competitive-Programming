#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,g;
    cin >> n >> g;
    vector<int> a(n),c(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        c[i]=n-i-1;
    }
    auto b=a;
    sort(b.begin(),b.end());
    pair<int,int> ans(1e9,-1);
    for(int i=0;i<n;i++){
        ans=min(ans,make_pair(abs(g-b[c[i]]),i));
    }
    cout << ans.second+1 << " " << ans.first << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}