#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    int l=0,r=n-1;
    while(l<r&&a[l]==b[l])l++;
    while(l<r&&a[r]==b[r])r--;
    int mn=n,mx=0;
    for(int i=l;i<=r;i++)mn=min(mn,a[i]),mx=max(mx,a[i]);
    while(0<l&&a[l-1]<=mn)mn=a[--l];
    while(r<n-1&&a[r+1]>=mx)mx=a[++r];
    cout << l+1 << ' ' << r+1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}