#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll inf=1e18;

// mt19937_64 rng(time(nullptr));

ll pw[20];

// const ll gen=rng()%inf;

ll ask(ll x){
    cout << "query " << x << endl;
    ll res=0;
    cin >> res;
    // ll tmp=x+gen;
    // while(tmp>0)res+=tmp%10,tmp/=10;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll ans=0;
    ll z=ask(0);
    for(ll d=1;d<1e18;d*=10){
        int l=1,r=10;
        while(l<r){
            int m=(l+r)/2;
            if(ask(m*d)<=z)r=m;
            else l=m+1;
        }
        ans+=(10-l)*d;
    }
    cout << "answer " << ans << endl;
    // cerr << gen << "\n";
}