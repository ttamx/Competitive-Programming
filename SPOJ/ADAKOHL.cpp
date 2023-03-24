#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

void runcase(){
    int n;
    cin >> n;
    vector<tuple<ld,ld,ld>> a(n);
    for(auto &[x,y,z]:a)cin >> x >> y >> z;
    ld ans=0;
    for(int i=0;i<n;i++){
        map<ld,ld> mp;
        auto [xi,yi,zi]=a[i];
        for(int j=0;j<n;j++){
            if(j==i)continue;
            auto [xj,yj,zj]=a[j];
            ld m=(xi-xj)/(yi-yj);
            if(yi==yj)m=1e18;
            if(xi==xj)m=0;
            mp[m]+=zj;
        }
        ans=max(ans,zi);
        for(auto [x,y]:mp)ans=max(ans,y+zi);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}