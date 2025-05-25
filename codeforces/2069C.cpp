#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    mint ans=0;
    mint c1=0,c2=0;
    for(auto x:a){
        if(x==1){
            c1++;
        }else if(x==2){
            c2*=2;
            c2+=c1;
        }else{
            ans+=c2;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}