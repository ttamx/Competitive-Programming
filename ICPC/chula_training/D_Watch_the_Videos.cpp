#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    long long ans=accumulate(a.begin(),a.end(),0LL)+n;
    if(n==1)cout << ans,exit(0);
    int l=0,r=n-1;
    int cur=0;
    while(l<r){
        while(l<r&&a[l]+a[r]<=m){
            l++;
            if(l<r){
                ans-=2;
                r--;
            }else{
                ans--;
                break;
            }
        }
        r--;
    }
    cout << ans << "\n";
}