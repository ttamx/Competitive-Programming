#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n,h;
ll lzl,lzr,ans;
multiset<ll> msl,msr;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> h;
    for(int i=1;i<=n;i++){
        ll x;
        cin >> x;
        if(i>1&&x<*msl.rbegin()+lzl){
            msl.emplace(x-lzl);
            msl.emplace(x-lzl);
            ll res=*msl.rbegin()+lzl;
            ans+=res-x;
            msl.erase(prev(msl.end()));
            msr.emplace(res-lzr);
        }else if(i>1&&x>*msr.begin()+lzr){
            msr.emplace(x-lzr);
            msr.emplace(x-lzr);
            ll res=*msr.begin()+lzr;
            ans+=x-res;
            msr.erase(msr.begin());
            msl.emplace(res-lzl);
        }else{
            msl.emplace(x-lzl);
            msr.emplace(x-lzr);
        }
        lzl-=h;
        lzr+=h;
    }
    cout << ans;
}