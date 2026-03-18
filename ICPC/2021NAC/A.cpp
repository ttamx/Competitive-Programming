#include<bits/stdc++.h>

using namespace std;

using ll = long long;

map<ll,ll> match;

void dnc(vector<ll> a,int d){
    if(a.empty())return;
    if(d<0){
        for(auto x:a)match[x]=x;
        return;
    }
    vector<ll> b[2];
    for(auto x:a)b[x>>d&1].emplace_back(x);
    dnc(b[0],d-1);
    dnc(b[1],d-1);
    for(auto x:b[1]){
        ll y=x^(1LL<<d);
        swap(match[x],match[y]);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    dnc(a,60);
    for(auto x:a)cout << match[x] << "\n";
}