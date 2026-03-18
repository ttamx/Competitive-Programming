#include "template.hpp"
#include "string/z-algorithm.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    string ans="";
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        int len=min(ans.size(),s.size());
        string t=s+ans.substr(ans.size()-len,len);
        auto z=z_algorithm(t);
        while(len>0&&z[t.size()-len]<len)len--;
        ans+=s.substr(len,s.size()-len);
    }
    cout << ans << "\n";
}