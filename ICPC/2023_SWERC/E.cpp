#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

struct Info{
    int h,d,i;
    Info(int _h,int _d,int _i):h(_h),d(_d),i(_i){};
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<Info> s;
    ll num=0,den=1;
    auto upd=[&](int x,int y,int z){
        // x+(y/z);
        int g=gcd(y,z);
        y/=g,z/=g;
        ll v=1LL*x*z+y;
        if(i128(v)*den>i128(num)*z){
            num=v,den=z;
        }
    };
    for(int i=1;i<n;i++){
        if(a[i]<a[i-1]){
            while(!s.empty()&&s.back().h<=a[i-1])s.pop_back();
            s.emplace_back(Info(a[i-1],a[i],i));
        }else if(!s.empty()){
            if(a[i]>s[0].h){
                if(a[i-1]<s[0].h){
                    upd(i-s[0].i,s[0].h-a[i-1],a[i]-a[i-1]);
                }
                s.clear();
            }else{
                while(!s.empty()&&s.back().h<=a[i])s.pop_back();
                auto &x=s.back();
                upd(i-x.i,a[i]-x.d,x.h-x.d);
            }
        }
    }
    if(den==1)cout << num;
    else cout << num << "/" << den;
}