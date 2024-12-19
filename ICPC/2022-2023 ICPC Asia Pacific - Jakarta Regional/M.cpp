#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<ll> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    bool f=false;
    for(int i=0;i<n;i++){
        if(a[i]+b[i]<0){
            f=true;
        }
    }
    a.insert(a.begin(),0);
    b.insert(b.begin(),0);
    for(int i=1;i<=n;i++){
        a.emplace_back(a[i]);
        b.emplace_back(b[i]);
    }
    for(int i=1;i<2*n;i++){
        a[i]+=a[i-1];
        b[i]+=b[i-1];
    }
    if(min(a[n],b[n])<0){
        f=true;
    }
    while(q--){
        int s,t;
        cin >> s >> t;
        s--,t--;
        if(f){
            cout << "flawed\n";
        }else{
            ll v1=(s<=t?(a[t]-a[s]):(a[t+n]-a[s]));
            ll v2=(t<=s?(b[s]-b[t]):(b[s+n]-b[t]));
            cout << min(v1,v2) << "\n";
        }
    }
}