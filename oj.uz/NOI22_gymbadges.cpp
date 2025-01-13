#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b(n),ord(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){return a[i]+b[i]<a[j]+b[j];});
    priority_queue<ll> pq;
    ll sum=0;
    for(int i:ord){
        pq.emplace(a[i]);
        sum+=a[i];
        if(sum>b[i]+a[i]){
            sum-=pq.top();
            pq.pop();
        }
    }
    cout << pq.size();
}