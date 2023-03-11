#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int mn=0,mx=1e9;
    for(int i=1;i<n;i++){
        if(a[i-1]<a[i]){
            mx=min(mx,(a[i-1]+a[i])/2);
        }else if(a[i-1]>a[i]){
            mn=max(mn,(a[i-1]+a[i]+1)/2);
        }
    }
    if(mn>mx)cout << -1 << '\n';
    else cout << mn << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}