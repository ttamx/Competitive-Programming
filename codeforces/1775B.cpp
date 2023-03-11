#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> a(n);
    map<int,int> mp;
    for(auto &v:a){
        int k;
        cin >> k;
        v.resize(k);
        for(auto &x:v){
            cin >> x;
            mp[x]++;
        }
    }
    for(auto v:a){
        bool ok=true;
        for(auto x:v)if(mp[x]==1)ok=false;
        if(ok){
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}