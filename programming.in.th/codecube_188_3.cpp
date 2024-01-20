#include<bits/stdc++.h>

using namespace std;

int n,q;
map<int,vector<int>> pos;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int val;
        cin >> val;
        pos[val].push_back(i);
    }
    while(q--){
        int l,r,c;
        cin >> l >> r >> c;
        auto first=lower_bound(pos[c].begin(),pos[c].end(),l);
        auto last=upper_bound(pos[c].begin(),pos[c].end(),r);
        cout << last-first << "\n";
    }
}