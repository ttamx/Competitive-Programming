#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<vector<int>> vec(k+2);
    for(int i=1;i<=k;i++)vec[i].emplace_back(0);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        vec[x].emplace_back(i);
    }
    for(int i=1;i<=k;i++)vec[i].emplace_back(n+1);
    int ans=n;
    for(int i=1;i<=k;i++){
        pair<int,int> mx;
        for(int j=1;j<vec[i].size();j++){
            mx.second=max(mx.second,vec[i][j]-vec[i][j-1]-1);
            if(mx.second>mx.first)swap(mx.first,mx.second);
        }
        mx.first=mx.first/2;
        if(mx.second>mx.first)swap(mx.first,mx.second);
        ans=min(ans,mx.first);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}