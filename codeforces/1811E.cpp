#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    ll n;
    cin >> n;
    vector<int> ans;
    while(n>0){
        ans.push_back(n%9);
        n/=9;
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << (x<4?x:x+1);
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}