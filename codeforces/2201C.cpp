#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    mint ans=0;
    for(int t=0;t<2;t++){
        char c='('+t;
        int bal=0;
        array<array<mint,2>,5> dp{};
        for(auto x:s){
            auto ndp=dp;
            if(x==c){
                for(int d=0;d<5;d++){
                    for(int e=0;e<2;e++){
                        if(bal+d+(e?-1:1)-2>=0){
                            ans+=dp[d][e];
                        }
                    }
                }
            }
            int dif=(x=='('?1:-1);
            for(int d=0;d<5;d++){
                for(int e=0;e<2;e++){
                    int v=d+(e?-1:1)-dif;
                    if(v>=0&&v<5&&bal+d+(e?-1:1)-2>=0){
                        ndp[v][x==')']+=dp[d][e];
                    }
                }
            }
            if(bal+(t?-1:1)>=0){
                ndp[(t?-1:1)-dif+2][x==')']++;
            }
            bal+=dif;
            dp=move(ndp);
            for(int d=0;d<5;d++){
                for(int e=0;e<2;e++){
                    if(bal+d-2<0){
                        dp[d][e]=0;
                    }
                }
            }
        }
    }
    cout << ans+n << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}