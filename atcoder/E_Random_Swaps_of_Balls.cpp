#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mint n;
    int k;
    cin >> n >> k;
    mint p1=1,p2=0;
    mint d=(n*n).inv();
    for(int i=0;i<k;i++){
        mint q1=(p1*(n+(n-1)*(n-2))+p2*2)*d;
        mint q2=(p1*(n-1)*2+p2*(n*n-2))*d;
        p1=q1;
        p2=q2;
    }
    cout << p1+p2/(n-1)*(n*(n+1)/2-1);
}