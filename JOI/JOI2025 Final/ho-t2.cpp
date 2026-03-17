#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;

int n;
ll a[N],b[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    for(int i=1;i<=n;i++){
        a[i+n]=a[i];
        b[i+n]=b[i];
    }
    ll sum=0;
    for(int i=1;i<=2*n;i++){
        b[i]+=b[i-1];
        a[i]-=b[i-1];
    }
    ll ans=1e18;
    deque<int> dq;
    for(int i=1;i<=n;i++){
        while(!dq.empty()&&a[dq.back()]<a[i]){
            dq.pop_back();
        }
        dq.emplace_back(i);
    }
    for(int i=n+1;i<=2*n;i++){
        while(!dq.empty()&&i-dq.front()>=n){
            dq.pop_front();
        }
        while(!dq.empty()&&a[dq.back()]<a[i]){
            dq.pop_back();
        }
        dq.emplace_back(i);
        ans=min(ans,a[dq.front()]+b[i-n]);
    }
    cout << max(ans,0LL) << "\n";
}