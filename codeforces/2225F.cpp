#include "template.hpp"
#include "string/suffix-array.hpp"

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    if(1LL*m*k>n){
        cout << "NO\n";
        return;
    }
    if(k==1){
        cout << "YES\n";
        cout << s << "\n";
        return;
    }
    SuffixArray sa(s);
    auto cmp=[&](int i,int leni,int j,int lenj){
        int lcp=sa.get_lcp(i,j);
        if(lcp>=min(leni,lenj))return leni<lenj;
        return s[i+lcp]<s[j+lcp];
    };
    int idx=-1,len=0;
    for(int i=0;i+m<=n;i++){
        if(i!=0&&i<m)continue;
        int r=n-(k-1-min(k-1,i/m))*m;
        if(r-i<m)continue;
        if(idx==-1||cmp(idx,len,i,r-i)){
            idx=i;
            len=r-i;
        }
    }
    cout << "YES\n";
    cout << s.substr(idx,len) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}