#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    if(a.size()<3||(a.size()==3&&a[2]-a[1]==a[1]-a[0])){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}