#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n-1);
    for(auto &x:b)cin >> x;
    a[0]=b[0];
    a[n-1]=b[n-2];
    for(int i=1;i<n-1;i++)a[i]=min(b[i-1],b[i]);
    for(auto x:a)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}