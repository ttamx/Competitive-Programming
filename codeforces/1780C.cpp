#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),c(m);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x--;
        a[x]++;
    }
    priority_queue<int> pq;
    for(auto x:a)pq.push(x);
    for(auto &x:c)cin >> x;
    sort(a.rbegin(),a.rend());
    sort(c.rbegin(),c.rend());
    int ans=0;
    for(auto x:c){
        int t=pq.top();
        pq.pop();
        ans+=min(t,x);
        pq.push(t-min(t,x));
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}