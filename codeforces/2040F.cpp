#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

const int N=3e6+5;
int phi[N];
mint ways[N];

void runcase(){
    int a,b,c,k;
    cin >> a >> b >> c >> k;
    vector<int> v(k);
    int n=a*b*c;
    int g=0;
    for(auto &x:v){
        cin >> x;
        g=gcd(g,x);
    }
    auto get_factor=[&](int x){
        vector<int> f;
        for(int i=1;i*i<=x;i++){
            if(x%i==0){
                f.emplace_back(i);
                if(i*i<x){
                    f.emplace_back(x/i);
                }
            }
        }
        return f;
    };
    auto fa=get_factor(a);
    auto fb=get_factor(b);
    auto fc=get_factor(c);
    auto fg=get_factor(g);
    for(auto d:fg){
        ways[d]=comb.fac(n/d);
        for(auto x:v){
            ways[d]*=comb.ifac(x/d);
        }
    }
    mint ans=0;
    for(auto da:fa){
        for(auto db:fb){
            for(auto dc:fc){
                int d=lcm(da,lcm(db,dc));
                ans+=ways[d]*phi[da]*phi[db]*phi[dc];
            }
        }
    }
    cout << ans/n << "\n";
    for(auto d:fg){
        ways[d]=0;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++){
        phi[i]+=i;
        for(int j=i*2;j<N;j+=i){
            phi[j]-=phi[i];
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}