#include "template.hpp"
#include "string/manacher.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    auto pal=manacher(s);
    vi dp1(n),dp2(n);
    for(int i=n-1;i>=0;i--){
        dp1[i]=i+1<n&&s[i]==s[i+1]?dp1[i+1]:i+1;
        dp2[i]=i+2<n&&s[i]==s[i+2]?dp2[i+2]:i+2;
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        ll ans=0;
        ll len=r-l+1;
        if(pal[l+r]<len)ans=len;
        if(dp1[l]<=r){
            ll x=(len-1)-(len-1)%2;
            ans+=(x/2)*(x+2)/2;
        }
        if(dp2[l]<=r||dp2[l+1]<=r){
            ll x=len-1-len%2;
            ans+=((x-1)/2)*(x+3)/2;
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}