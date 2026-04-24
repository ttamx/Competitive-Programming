#include "template.hpp"
#include "string/manacher.hpp"

void runcase(){
    string s;
    cin >> s;
    int l=0,r=SZ(s)-1;
    while(l<r&&s[l]==s[r])l++,r--;
    auto a=manacher(s);
    pair<int,int> best(0,0);
    for(int i=l;i<=r;i++){
        if(a[l+i]>=i-l+1)best=max(best,mp(i-l+1,l));
        if(a[r+i]>=r-i+1)best=max(best,mp(r-i+1,i));
    }
    cout << s.substr(0,l) << s.substr(best.se,best.fi) << s.substr(r+1,l) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}