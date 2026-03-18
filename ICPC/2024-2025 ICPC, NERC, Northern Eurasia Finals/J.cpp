#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    int n,m,q;
    cin >> n >> m >> q;
    vector<ll> a(n),d(n),l(m),t(q);
    ll tot=0;
    for(auto &x:a){
        cin >> x;
        tot+=x;
    }
    for(auto &x:d){
        cin >> x;
    }
    for(auto &x:l){
        cin >> x;
    }
    for(auto &x:t){
        cin >> x;
    }
    vector<int> ord(n),qord(q);
    iota(ord.begin(),ord.end(),0);
    iota(qord.begin(),qord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return d[i]<d[j];
    });
    sort(qord.begin(),qord.end(),[&](int i,int j){
        return t[i]>t[j];
    });
    vector<ll> b(q);
    ll last=1e18;
    for(auto i:qord){
        while(!ord.empty()&&d[ord.back()]>t[i]){
            int j=ord.back();
            ord.pop_back();
            last=min(last,d[j]);
            last-=a[j];
            tot-=a[j];
        }
        b[i]=min(last,t[i])-tot;
    }
    for(int i=1;i<m;i++){
        l[i]+=l[i-1];
    }
    for(auto x:b){
        cout << upper_bound(l.begin(),l.end(),x)-l.begin() << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}