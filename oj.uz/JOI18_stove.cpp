#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,k;
int a[N];
int ans=0;
priority_queue<int> pq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=2;i<=n;i++)pq.emplace(a[i]-a[i-1]);
    for(int i=1;i<k;i++)pq.pop();
    while(!pq.empty())ans+=pq.top(),pq.pop();
    cout << ans+k;
}