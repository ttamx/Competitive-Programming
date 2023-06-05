#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a)cin >> x >> y,y=-y;
    sort(a.begin(),a.end());
    int mx=0,cur=0;
    long long ans=0;
    queue<int> q;
    for(auto [x,y]:a){
        if(x<=mx)continue;
        ans-=y;
        q.emplace(x);
        mx=max(mx,(int)q.size());
        while(!q.empty()&&q.front()<=mx)q.pop();
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}