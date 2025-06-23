#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string a,b;
    cin >> a >> b;
    array<int,26> cnt{};
    for(auto x:a)cnt[x-'a']++;
    auto calc=[&](string s){
        mint res=0;
        auto cc=cnt;
        for(int i=0;i<s.size();i++){
            for(int c=0;c<s[i]-'a';c++){
                if(cc[c]==0)continue;
                cc[c]--;
                mint cur=1;
                int sz=s.size()-i-1;
                for(int j=0;j<26;j++){
                    cur*=comb.C(sz,cc[j]);
                    sz-=cc[j];
                }
                cc[c]++;
                res+=cur;
            }
            if(--cc[s[i]-'a']<0){
                break;
            }
        }
        return res;
    };
    cout << calc(b)-calc(a)-1 << "\n";
}