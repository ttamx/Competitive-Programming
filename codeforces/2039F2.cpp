#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=1e6+5;

int mob[N];
vector<int> factor[N];
mint dp[N],aux[N],ans[N],base;

void runcase(){
    int n;
    cin >> n;
    cout << ans[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mob[1]=1;
    for(int i=1;i<N;i++){
        for(int j=i;j<N;j+=i){
            factor[j].emplace_back(i);
        }
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
        }
    }
    for(int i=1;i<N;i++){
        for(auto g:factor[i]){
            mint res=dp[g]+1;
            for(auto d:factor[g]){
                res+=aux[d];
            }
            res*=2;
            dp[g]-=res;
            for(auto d:factor[i/g]){
                aux[d*g]+=res*mob[d];
            }
        }
        base+=dp[i]+1;
        for(auto d:factor[i]){
            base+=aux[d];
        }
        ans[i]=base;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}