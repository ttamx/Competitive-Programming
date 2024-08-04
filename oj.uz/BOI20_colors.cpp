#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll n;

inline int ask(ll x){
    cout << "? " << x << endl;
    int res;
    cin >> res;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    ll pos=1,dir=1,st=1,step=0;
    int cnt=0;
    for(ll i=n;i>1;i=(i+1)/2){
        step+=i/2;
        pos+=dir*step;
        if(pos<1){
            ll dif=1-pos;
            pos+=dif,st+=dif;
        }
        dir=-dir;
    }
    ll ans=1;
    ask(st);
    dir=1,step=0;
    for(ll i=n;i>1;){
        st+=dir*(step+i/2);
        if(!ask(st)){
            ans+=i/2;
            step+=i/2;
            i=(i+1)/2;
        }else{
            i=i/2;
        }
        dir=-dir;
    }
    cout << "= " << ans << endl;
}