#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll LIM=1e15;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(auto &x:a){
            cin >> x;
        }
        auto check=[&](ll mid){
            ll l=0,r=mid,cl=0,cr=mid;
            int b=0;
            for(auto x:a){
                b^=1;
                tie(l,r)=make_pair(x-r,x-l);
                if(l<0){
                    if(b)cr+=l;
                    else cl-=l;
                    l=0;
                }
                if(r>mid){
                    if(b)cl+=r-mid;
                    else cr-=r-mid;
                    r=mid;
                }
                if(l>r||cl>cr)return false;
            }
            l=max(l,cl);
            r=min(r,cr);
            if(b){
                assert((r-l)%2==0);
                l=r=(l+r)/2;
            }
            auto calc=[&](ll v){
                ll res=0,st=v;
                for(auto x:a){
                    res+=v;
                    v=x-v;
                    if(v<0||v>mid)return __int128_t(1e30);
                }
                return __int128_t(res);
            };
            if(__int128_t(mid)*n-calc(l)>=mid)return true;
            if(__int128_t(mid)*n-calc(r)>=mid)return true;
            return false;
        };
        ll l=0,r=LIM+1;
        while(l<r){
            ll m=(l+r)/2;
            if(check(m))r=m;
            else l=m+1;
        }
        assert(l<=LIM);
        cout << l << "\n";
    }
}