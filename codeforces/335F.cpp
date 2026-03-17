#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    ll sum=0;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
        sum+=x;
    }
    sort(a.begin(),a.end());
    int st=0;
    ll base=0;
    priority_queue<int> pq;
    auto dbg=[&](){
        ll cur=base;
        auto t=pq;
        cerr << st << " : ";
        cerr << cur << " ";
        while(!t.empty()){
            cur+=t.top();
            t.pop();
            cerr << cur << " ";
        }
        cerr << "\n";
    };
    int free=0;
    int tot=0;
    while(!a.empty()){
        ll v=a.back();
        int cnt=0;
        for(;!a.empty()&&a.back()==v;cnt++)a.pop_back();
        free=max(free,min(cnt,tot));
        tot+=cnt;
    }
    cout << sum-base << "\n";   
}   