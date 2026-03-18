#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,c;
    cin >> n >> c;
    string s;
    cin >> s;
    if(s[0]=='0'||s.back()=='0'){
        cout << -1 << "\n";
        return;
    }
    c/=gcd(c,2);
    mint ans=2;
    vector<int> a;
    for(int i=1;i+1<n;i++){
        if(s[i]=='1'){
            c/=gcd(c,2);
            ans*=2;
        }else if(s[i]=='0'){
            c/=gcd(c,i);
            ans*=i;
        }else if(i>1){
            if(i%2==0){
                c/=gcd(c,2);
                ans*=2;
            }else{
                a.emplace_back(i);
            }
        }
    }
    if(c!=(c&-c)){
        for(auto x:a){
            c/=gcd(c,2);
            ans*=2;
        }
    }else{
        while(!a.empty()&&c>2){
            c/=2;
            ans*=2;
            a.pop_back();
        }
        for(auto x:a){
            ans*=x;
        }
    }
    if(c==1){
        cout << -1 << "\n";
    }else{
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}