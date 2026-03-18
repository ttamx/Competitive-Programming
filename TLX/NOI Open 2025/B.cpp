#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = uint64_t;

const int K=200000;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<ull> f(n+1);
    for(int i=0;i<n;i++){
        f[i+1]=f[i]+a[i];
    }
    vector<ll> b{0};
    ull mul=1;
    ull block=1;
    for(int i=0;i<k;i++){
        if(b.size()<K){
            block*=2;
            int m=b.size();
            for(int i=0;i<m;i++){
                b[i]*=2;
                b.emplace_back(b[i]+n);
            }
        }else{
            mul=min(mul*2,(ull)n);
        }
    }
    if(b.size()>K){
        b.resize(K);
    }
    auto query=[&](ull i){
        ull j=i/block;
        ull k=i%block;
        assert(j<=n);
        ull res=f[j]*block;
        if(k>0)res+=ull(a[j])*ull(k);
        return res;
    };
    ull pre=n/mul;
    ull suf=n%mul;
    for(auto &x:b){
        ull res=0;
        res+=(query(x+pre)-query(x))*mul;
        res+=(query(x+pre+1)-query(x+pre))*suf;
        cout << res << "\n";
    }
}