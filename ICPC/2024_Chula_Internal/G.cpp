#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,h,q;
    cin >> n >> m >> h >> q;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    multiset<int> ms;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        ms.emplace(x);
    }
    vector<int> ans;
    for(auto [x,y]:a){
        auto it=ms.lower_bound(abs(y-h));
        if(it!=ms.end()){
            ms.erase(it);
            ans.emplace_back(x);
        }
    }
    while(q--){
        int x;
        cin >> x;
        x--;
        cout << (x<ans.size()?ans[x]:-1) << "\n";
    }
}