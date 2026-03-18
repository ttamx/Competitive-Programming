#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;
using i128 = __int128_t;

const int X=1e7+5;
const int E=60;

bool composite[X];
ll inv[E];
vector<int> primes;

ll n,a,b;
vector<pair<ll,int>> factors;
mint h[E];

mint solve(int i,ll x,mint ways){
    if(i==factors.size()){
        return ways;
    }
    mint res=0;
    auto [p,e]=factors[i];
    for(int j=0;j<=e;j++){
        res+=solve(i+1,x,ways*h[j]*h[e-j]);
        if(i128(x)*p>a)break;
        x*=p;
    }
    return res;
}

void runcase(){
    cin >> n >> a >> b;
    for(auto p:primes){
        int c=0;
        while(b%p==0){
            b/=p;
            c++;
        }
        if(c>0){
            factors.emplace_back(p,c);
        }
    }
    if(b>1){
        factors.emplace_back(b,1);
    }
    for(int i=0;i<E;i++){
        mint res=1;
        for(int j=1;j<=i;j++){
            res*=mint(n+i-j)/mint(j);
        }
        h[i]=res;
    }
    cout << solve(0,1LL,1LL) << "\n";
    factors.clear();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<X;i++){
        if(composite[i])continue;
        primes.emplace_back(i);
        for(int j=i*2;j<X;j+=i){
            composite[j]=true;
        }
    }
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}

/*
Case #1: 3
Case #2: 12
Case #3: 16
Case #4: 229471373
Case #5: 1
Case #6: 1
Case #7: 563322525
Case #8: 7221875
Case #9: 401950019
Case #10: 30276434
Case #11: 995424053
Case #12: 695328793
Case #13: 450655641

*/