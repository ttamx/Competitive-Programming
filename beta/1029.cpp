#include<bits/stdc++.h>

using namespace std;

int n,m,q;
set<int> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    while(m--){
        int x,y;
        cin >> x >> y;
        if(!s.emplace(x).second)s.erase(x);
        x+=y;
        if(!s.emplace(x).second)s.erase(x);
    }
    s.emplace(1);
    s.emplace(n+1);
    while(q--){
        int x;
        cin >> x;
        auto it=s.upper_bound(x);
        cout << *it-*prev(it) << '\n';
    }
}