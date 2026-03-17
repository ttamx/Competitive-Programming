#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> ans,c[2];
        int cur=0;
        for(auto ch:s){
            int x=ch-'0';
            if(c[x].empty()){
                c[x].emplace_back(++cur);
            }
            int i=c[x].back();
            c[x].pop_back();
            ans.emplace_back(i);
            c[x^1].emplace_back(i);
        }
        cout << cur << "\n";
        for(auto x:ans)cout << x << " ";
        cout << "\n";
    }
}