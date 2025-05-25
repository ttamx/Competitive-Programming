#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1005;

int dp[N];

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<ll> p;
    p.emplace_back(1);
    for(ll i=k;i<=1e9;i*=i){
        p.emplace_back(i+1);
    }
    int nimber=0;
    for(auto x:a){
        int cnt=upper_bound(p.begin(),p.end(),x)-p.begin();
        if(cnt%2==1){
            nimber^=1;
        }else{
            nimber^=2;
        }
    }
    cout << (nimber?"First":"Second") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}