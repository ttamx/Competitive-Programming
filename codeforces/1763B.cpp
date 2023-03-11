#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n,k;
    cin >> n >> k;
    vector<pair<long long,long long>> a(n);
    for(int i=0;i<n;i++)cin >> a[i].first;
    for(int i=0;i<n;i++)cin >> a[i].second;
    sort(a.begin(),a.end());
    for(int i=n-2;i>=0;i--)a[i].second=min(a[i].second,a[i+1].second);
    long long cur=0;
    k+=a[0].second;
    for(int i=0;i<n;i++){
        while(k>0&&cur<a[i].first){
            k-=a[i].second;
            cur+=k;
        }
    }
    if(cur<a[n-1].first)cout << "NO\n";
    else cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}