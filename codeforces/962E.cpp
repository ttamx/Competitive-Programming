#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<ll,char>> a(n);
    bool fb=false,fr=false;
    for(auto &[x,c]:a){
        cin >> x >> c;
        if(c=='B')fb=true;
        if(c=='R')fr=true;
    }
    if(!fb||!fr){
        cout << a.back().first-a[0].first << "\n";
        exit(0);
    }
    vector<int> b;
    for(int i=0;i<n;i++)if(a[i].second=='P')b.emplace_back(i);
    if(b.empty()){
        ll lb=1e18,rb=-1e18;
        ll lr=1e18,rr=-1e18;
        for(auto &[x,c]:a){
            if(c=='B'){
                lb=min(lb,x);
                rb=max(rb,x);
            }
            if(c=='R'){
                lr=min(lr,x);
                rr=max(rr,x);
            }
        }
        cout << rb-lb+rr-lr << "\n";
        exit(0);
    }
    for(int i=0;i+1<b.size();i++){
        ll l=a[b[i]].first,r=a[b[i+1]].first;
        ll d=r-l;

    }
}