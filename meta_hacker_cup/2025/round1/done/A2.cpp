#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    using P = pair<int,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    for(int i=0;i<n;i++){
        pq.emplace(a[i],i);
    }
    vector<bool> vis(n);
    int cnt=0,ans=0;
    while(cnt<n){
        auto [d,i]=pq.top();
        pq.pop();
        if(vis[i])continue;
        vis[i]=true;
        cnt++;
        ans=max(ans,d);
        if(i>0)pq.emplace(abs(a[i]-a[i-1]),i-1);
        if(i+1<n)pq.emplace(abs(a[i]-a[i+1]),i+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}