#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2),b(n+2),c(n+2);
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r;
        int l2=n-r,r2=n-l;
        if(min(r,r2)<max(l,l2)){
            a[l]++;
            a[r+1]--;
            a[l2]++;
            a[r2+1]--;
            b[l]++;
            b[r+1]--;
        }else{
            a[min(l,l2)]++;
            a[max(r,r2)+1]--;
            b[l]++;
            b[r+1]--;
            b[max(l,l2)]--;
            b[min(r,r2)+1]++;
            c[max(l,l2)]++;
            c[min(r,r2)+1]--;
        }
    }
    mint ans=0;
    for(int i=1;i<=n;i++){
        a[i]+=a[i-1];
        b[i]+=b[i-1];
        c[i]+=c[i-1];
        if(a[i]<n)continue;
        int x=i-b[i];
        if(x<0||x>c[i])continue;
        ans+=comb.C(c[i],x);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}