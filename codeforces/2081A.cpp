#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const mint INV = mint(2).inv();

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    mint ans=0;
    mint cur=1;
    for(int i=1;i<n;i++){
        cur*=INV;
        if(s[i]=='1'){
            ans+=cur;
        }
    }
    cout << n-1+ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}