#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    map<int,int> cx,cy;
    for(auto &[x,y]:a){
        cin >> x >> y;
        cx[x]++,cy[y]++;
    }
    long long ans=0;
    for(auto [x,y]:a)ans+=1LL*(cx[x]-1)*(cy[y]-1);
    cout << ans << "\n";
}