#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        pq.push(x);
    }
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        pq.pop();
        pq.push(x);
    }
    long long ans=0;
    while(!pq.empty()){
        ans+=pq.top();
        pq.pop();
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}