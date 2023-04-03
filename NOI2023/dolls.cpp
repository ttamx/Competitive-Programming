#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    set<pair<int,int>> s;
    int ans=0;
    s.emplace(-2e9,-2e9);
    while(n--){
        int x;
        cin >> x;
        auto it=s.lower_bound({x+1,0});
        if(prev(it)->second<x){
            int l=x,r=x;
            while(it!=s.begin()&&prev(it)->second+1==l){
                l=prev(it)->first;
                ans-=(prev(it)->second-prev(it)->first+2)/2;
                s.erase(prev(it));
            }
            while(it!=s.end()&&it->first-1==r){
                r=it->second;
                ans-=(it->second-it->first+2)/2;
                it=s.erase(it);
            }
            ans+=(r-l+2)/2;
            s.emplace(l,r);
        }
        cout << ans << ' ';
    }
}