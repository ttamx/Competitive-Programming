#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    multiset<int> l,r;
    for(auto &[x,y]:a){
        cin >> x >> y;
        l.insert(x);
        r.insert(y);
    }
    int ans=0;
    for(auto [x,y]:a){
        l.erase(l.lower_bound(x));
        r.erase(r.lower_bound(y));
        ans=max(ans,*r.begin()-*prev(l.end()));
        l.insert(x);
        r.insert(y);
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}