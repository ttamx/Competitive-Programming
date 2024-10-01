#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> p(2*n);
    for(auto &x:p){
        cin >> x;
    }
    int small=0,big=0,both=0;
    for(int i=0;i<2*n;i+=2){
        if(p[i]!=0){
            (p[i]<=n?small:big)++;
        }else{
            both++;
        }
    }
    mint ans=1;
    for(int i=big+both;i>=1;i--){
        ans*=i;
    }
    for(int i=small+both;i>=1;i--){
        ans*=i;
    }
    for(int i=0;i<both;i++){
        ans*=2;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}