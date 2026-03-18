#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    cin >> m;
    vector<int> b(m);
    for(auto &x:b)cin >> x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int i=0,ans=0;
    for(auto x:a){
        while(i<m&&b[i]<x-1)i++;
        if(i<m&&b[i]<=x+1){
            i++;
            ans++;
        }
    }
    cout << ans << "\n";
}