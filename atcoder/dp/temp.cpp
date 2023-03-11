#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=1e9+7;

struct mint{
    ll val;
    mint():val(0){}
    mint(ll _val):val(_val%mod){}
    mint& operator+=(mint o){val=(val+o.val)%mod;return *this;}
    mint& operator-=(mint o){val=(val+mod-o.val)%mod;return *this;}
    mint& operator*=(mint o){val=(val*o.val)%mod;return *this;}
    friend mint operator+(mint lhs,mint rhs){return lhs+=rhs;};
    friend mint operator-(mint lhs,mint rhs){return lhs-=rhs;};
    friend mint operator*(mint lhs,mint rhs){return lhs*=rhs;};
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(10);
    t=10;
    mint x=1e9,y=10;
    mint z=x+y;
    z+=5;
    cout << z.val;
}