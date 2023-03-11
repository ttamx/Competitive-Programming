#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll x,y;
bool ok;
map<ll,bool> vis;

ll rev(ll num){
    ll res=0;
    while(num){
        res<<=1;
        res+=num&1;
        num>>=1;
    }
    return res;
}

void sol(ll num){
    if(vis[num])return;
    vis[num]=true;
    if(num==x)ok=true;
    if(ok)return;
    if((num&1)==0)return;
    ll res=rev(num);
    sol(res);
    sol(res>>1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> x >> y;
    sol(y);
    x=rev(x);
    vis.clear();
    sol(y);
    cout << (ok?"YES":"NO");
}