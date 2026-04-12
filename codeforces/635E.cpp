#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int d,n,m;
    cin >> d >> n >> m;
    vector<pair<int,int>> a(m);
    for(auto &[x,p]:a){
        cin >> x >> p;
    }
    a.emplace_back(d,0);
    sort(a.begin(),a.end());
    deque<pair<int,int>> dq;
    ll ans=0;
    int pos=0;
    dq.emplace_back(0,n);
    for(auto [x,p]:a){
        while(!dq.empty()&&pos<x){
            auto [price,last]=dq.front();
            if(pos<last){
                int tar=min(last,x);
                ans+=1LL*(tar-pos)*price;
                pos=tar;
            }
            if(last<=pos){
                dq.pop_front();
            }
        }
        if(pos<x){
            cout << "-1\n";
            exit(0);
        }
        while(!dq.empty()&&dq.back().first>=p){
            dq.pop_back();
        }
        dq.emplace_back(p,x+n);
    }
    cout << ans << "\n";
}