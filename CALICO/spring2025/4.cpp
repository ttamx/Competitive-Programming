#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(n*m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int x;
            cin >> x;
            x--;
            a[x]={i,j};
        }
    }
    a.insert(a.begin(),{0,0});
    long long ans=0;
    for(int i=0;i<n*m;i++){
        int dx=abs(a[i].first-a[i+1].first);
        int dy=abs(a[i].second-a[i+1].second);
        ans+=min(dx,n-dx)+min(dy,m-dy);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}