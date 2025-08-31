#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    vector<ll> v;
    for(int i=0;i+1<n;i++){
        v.emplace_back(a[i+1]-a[i]);
    }
    vector<ll> add,sub;
    add.emplace_back(0);
    ll val=0;
    for(int i=0;i<n-1;i++){
        val=v[i]-val;
        (i%2==1?add:sub).emplace_back(val);
    }
    sort(add.rbegin(),add.rend());
    sort(sub.rbegin(),sub.rend());
    sort(b.begin(),b.end());
    auto work=[&](ll x){
        vector<ll> c;
        for(auto e:add){
            c.emplace_back(e+x);
        }
        for(auto e:sub){
            c.emplace_back(e-x);
        }
        sort(c.begin(),c.end());
        if(b==c){
            vector<ll> ans;
            ans.emplace_back(x);
            for(int i=0;i<n-1;i++){
                x=v[i]-x;
                ans.emplace_back(x);
            }
            for(auto e:ans){
                cout << e << " ";
            }
            cout << "\n";
            exit(0);
        }
    };
    ll mx=b.back();
    if(!add.empty()){
        work(mx-add[0]);
    }
    if(!sub.empty()){
        work(sub[0]-mx);
    }
    assert(false);
}