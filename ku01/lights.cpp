#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    int ans=0,tmp=0;
    for(auto x:a){
        tmp+=x;
        ans+=tmp;
    }
    cout << ans*2;
}