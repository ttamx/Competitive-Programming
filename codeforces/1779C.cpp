#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    m--;
    vector<long long> a(n);
    for(auto &x:a)cin >> x;
    int ans=0;
    long long res=0;
    priority_queue<long long> pq;
    for(int i=m+1;i<n;i++){
        res+=a[i];
        if(a[i]<0)pq.push(-a[i]*2);
        while(res<0){
            ans++;
            res+=pq.top();
            pq.pop();
        }
    }
    while(!pq.empty())pq.pop();
    res=0;
    for(int i=m;i>0;i--){
        res+=a[i];
        if(a[i]>0)pq.push(a[i]*2);
        while(res>0){
            ans++;
            res-=pq.top();
            pq.pop();
        }
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}