#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k,q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int idx=-1;
    long long ans=0;
    for(int i=0;i<n;i++){
        idx=max(i-1,idx);
        while(idx+1<n&&a[idx+1]<=q)idx++;
        ans+=max(0,idx-(i+k-1)+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}