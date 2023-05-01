#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    long long n;
    int q;
    cin >> n >> q;
    auto sqrt=[&](long long x){
        long long l=0,r=1e9;
        while(l<r){
            long long m=(l+r+1)/2;
            if(m*m<=x)l=m;
            else r=m-1;
        }
        return l;
    };
    auto calc=[&](long long x){
        return sqrt(x)+sqrt(x/2);
    };
    while(q--){
        long long l,r;
        cin >> l >> r;
        cout << calc(r)-calc(l-1) << "\n";
    }
}