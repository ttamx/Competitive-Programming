    #include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

mint binpow(mint a,int b){
    mint res=1;
    while(b>0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

const int N=2e5+5;
const int S=13;

int mob[N],pc[N];
bool composite[N];
vector<int> divisors[N];

void runcase(){
    int n,k;
    cin >> n >> k;
    array<mint,S> pw{};
    for(int i=0;i<S;i++){
        pw[i]=binpow(i,k);
    }
    vector<array<mint,S>> cnt(n+1,array<mint,S>{});
    mint ans=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        for(auto g:divisors[x]){
            array<mint,S> cur{};
            for(auto d:divisors[x/g]){
                for(int j=0;j<=6;j++){
                    cur[j]+=cnt[g*d][j]*mob[d];
                }
            }
            for(int j=0;j<=6;j++){
                ans+=cur[j]*pw[j+pc[x]-pc[g]];
            }
        }
        for(auto d:divisors[x]){
            cnt[d][pc[x]]++;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mob[1]=1;
    composite[1]=true;
    for(int i=1;i<N;i++){
        if(!mob[i])continue;
        if(!composite[i]){
            for(int j=i;j<N;j+=i){
                pc[j]++;
                assert(pc[j]<=6);
            }
            for(int j=i*2;j<N;j+=i){
                composite[j]=true;
            }
        }
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
        }
        for(int j=i;j<N;j+=i){
            divisors[j].emplace_back(i);
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}