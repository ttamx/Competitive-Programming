#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<ll,ll> dat;
    auto upd=[&](ll x,ll v){
        if((dat[x]+=v)==0)dat.erase(x);
    };
    for(int i=0;i<n;i++){
        char c;
        ll x,len;
        cin >> c >> len >> x;
        if(c=='|'){
            upd(x,len);
            upd(x+1,-len);
            cout << "S";
        }else{
            ll l=x,r=x+len-1;
            auto it=dat.lower_bound(l+1);
            if(it==dat.end()||it->first>r){
                upd(l,+1);
                upd(r+1,-1);
                cout << "S";
            }else{
                cout << "U";
            }
        }
    }
}