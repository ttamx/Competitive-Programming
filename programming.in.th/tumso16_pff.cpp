#include<bits/stdc++.h>

using namespace std;

const int N=8005;
const int K=8e5+5;

int n,m;
int sum[K];
int a[N];
vector<pair<int,int>> v;
set<int> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<K;i++)for(int j=i;j<K;j+=i)sum[j]+=i;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        int t;
        cin >> t;
        if(sum[a[i]]%a[i]==0&&a[i]-(a[i]&-a[i]))v.emplace_back(t,a[i]);
    }
    if(v.size()<m)cout << -1,exit(0);
    sort(v.begin(),v.end());
    v.erase(v.begin()+m,v.end());
    long long ans=0;
    for(auto &[x,y]:v)ans+=x,s.emplace(y);
    cout << ans << '\n';
    for(auto &x:s)cout << x << '\n';
}