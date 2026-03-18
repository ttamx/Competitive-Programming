#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    mint ans0=0,ans1=0;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int x=0;x<=i;x++){
                for(int y=0;y<=j;y++){
                    if((i!=x||j!=y)&&a[i][j]==a[x][y]){
                        if(a[i][j]=='0'){
                            ans0+=comb.C((i-x)+(j-y),(i-x));
                        }else{
                            ans1+=comb.C((i-x)+(j-y),(i-x));
                        }
                    }
                }
            }
        }
    }
    cout << ans0 << " " << ans1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}