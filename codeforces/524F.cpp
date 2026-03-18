#include "template.hpp"
#include "string/suffix-array.hpp"

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    s+=s;
    SuffixArray sa(s);
    vector<int> f(n+1);
    for(int i=0;i<n;i++){
        f[i+1]=f[i]+(s[i]=='('?1:-1);
    }
    auto suf=f;
    for(int i=n-1;i>=0;i--){
        suf[i]=min(suf[i],suf[i+1]);
    }
    int bal=f[n];
    if(bal>=0){
        int pre=0;
        int best=-1;
        for(int i=0;i<n;i++){
            pre=min(pre,f[i]);
            if(suf[i]-f[i]<0||bal+pre-f[i]<0)continue;
            if(best==-1||sa.isa[i]<sa.isa[best]){
                best=i;
            }
        }
        assert(best!=-1);
        cout << s.substr(best,n)+string(bal,')') << "\n";
    }else{
        int pre=0;
        int add=-bal;
        int best=-1;
        for(int i=0;i<n;i++){
            pre=min(pre,f[i]);
            if(add+suf[i]-f[i]<0||add+bal+pre-f[i]<0)continue;
            if(best==-1||sa.isa[i]<sa.isa[best]){
                best=i;
            }
        }
        assert(best!=-1);
        cout << string(add,'(')+s.substr(best,n) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}