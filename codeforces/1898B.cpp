#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    long long ans=0;
    for(int i=n-2;i>=0;i--){
        if(a[i]<=a[i+1])continue;
        int d=(a[i]-1)/a[i+1]+1;
        ans+=d-1;
        a[i]/=d;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}