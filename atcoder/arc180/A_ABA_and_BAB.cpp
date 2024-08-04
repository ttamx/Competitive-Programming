#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    string s;
    cin >> n >> s;
    mint ans=1;
    for(int i=0;i<n;i++){
        int j=i;
        while(j+1<n&&s[j+1]!=s[j])j++;
        int sz=j-i+1;
        if(sz<3)continue;
        ans*=(sz+1)/2;
        i=j;
    }
    cout << ans;
}