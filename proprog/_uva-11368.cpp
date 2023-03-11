#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> v(10001);
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        v[x].push_back(y);
    }
    int ans=n;
    multiset<int> ms;
    for(int i=10000;i>0;i--){
        sort(v[i].begin(),v[i].end());
        for(auto x:v[i]){
            auto it=ms.upper_bound(x);
            if(it!=ms.end()){
                ans--;
                ms.erase(it);
            }
        }
        for(auto x:v[i])ms.emplace(x);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}