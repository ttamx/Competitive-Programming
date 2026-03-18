#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> ans;
    if(n&1){
        n-=3;
        ans.emplace_back(3);
    }
    while(n>0){
        ans.emplace_back(2);
        n-=2;
    }
    cout << ans.size() << "\n";
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}