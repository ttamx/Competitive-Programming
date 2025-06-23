#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;
using P = pair<ll,ll>;

i128 cross(P a,P b){
    return i128(a.first)*b.second-i128(a.second)*b.first;
}

i128 cross(P a,P b,P o){
    a.first-=o.first;
    a.second-=o.second;
    b.first-=o.first;
    b.second-=o.second;
    return cross(a,b);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<P> a(n);
    for(auto &[x,y]:a){
        cin >> x >> y;
        y-=x*x;
    }
    sort(a.begin(),a.end());
    vector<P> b;
    for(auto p:a){
        if(!b.empty()&&b.back().first==p.first){
            b.pop_back();
        }
        b.emplace_back(p);
    }
    vector<P> hull;
    for(auto p:b){
        while(hull.size()>=2&&cross(hull.back(),p,hull.end()[-2])>=0){
            hull.pop_back();
        }
        hull.emplace_back(p);
    }
    cout << hull.size()-1 << "\n";
}