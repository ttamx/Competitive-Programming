#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,t;
    cin >> n >> t;
    int ans=0;
    priority_queue<int> pq;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        while(!pq.empty()&&pq.top()>=t-i)pq.pop();
        if(max(x,i)<t)pq.emplace(x-i);
        ans=max(ans,(int)pq.size());
    }
    cout << ans;
}