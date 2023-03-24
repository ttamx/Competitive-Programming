#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

void runcase(){
    int n;
    cin >> n;
    vector<pair<ld,ld>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    sort(a.rbegin(),a.rend());
    ld mx=0,ans=0;
    for(int i=1;i<n;i++){
        if(a[i].second>mx){
            ld x=llabs(a[i].first-a[i-1].first);
            ld y=llabs(a[i].second-a[i-1].second);
            ld d=sqrt(x*x+y*y);
            ans+=d*(a[i].second-mx)/y;
            mx=a[i].second;
        }
    }
    cout << fixed << setprecision(2) << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}