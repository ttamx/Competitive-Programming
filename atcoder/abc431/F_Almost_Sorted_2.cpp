#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,d;
    cin >> n >> d;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.begin(),a.end());
    mint ans=1;
    for(int i=0,j=0;i<n;i++){
        while(a[j]<a[i]-d){
            j++;
        }
        ans*=i-j+1;
    }
    for(int i=0;i<n;i++){
        int s=1;
        while(i+1<n&&a[i]==a[i+1]){
            i++,s++;
            ans*=comb.inv(s);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}