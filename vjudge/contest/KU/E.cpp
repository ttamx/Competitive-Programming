#include<bits/stdc++.h>

using namespace std;

using db = long double;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<pair<int,int>> a(9);
    for(int i=0;i<3;i++)for(int j=0;j<3;j++){
        int x;
        cin >> x;
        a[x-1]={i,j};
    }
    db ans=0;
    for(int i=1;i<9;i++){
        int dx=a[i].first-a[i-1].first;
        int dy=a[i].second-a[i-1].second;
        ans+=sqrtl(dx*dx+dy*dy);
    }
    cout << fixed << setprecision(10) << ans;
}