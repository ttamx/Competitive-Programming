#include "template.hpp"

void runcase(){
    int n;
    cin >> n;
    string a,b;
    cin >> a >> b;
    auto calc=[](string a,string b){
        int n=a.size();
        for(int i=1;i+1<n;i++)if(a[i-1]=='0'&&a[i+1]=='0')b[i]='1';
        for(int i=1;i+1<n;i++)if(b[i-1]=='1'&&b[i+1]=='1')a[i]='1';
        return a;
    };
    auto c=calc(a,b);
    vector<int> cnt(n);
    for(int i=0;i<n;i++)cnt[i]=cnt[i-1]+(c[i]=='1');
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        if(r-l+1<6){
            int ans=0;
            for(auto x:calc(a.substr(l,r-l+1),b.substr(l,r-l+1)))ans+=x=='1';
            cout << ans << "\n";
        }else{
            int nl=l+3,nr=r-3;
            int ans=cnt[nr]-cnt[nl-1];
            auto sl=calc(a.substr(l,5),b.substr(l,5));
            auto sr=calc(a.substr(r-4,5),b.substr(r-4,5));
            for(int i=0;i<3;i++)ans+=sl[i]=='1';
            for(int i=0;i<3;i++)ans+=sr[4-i]=='1';
            cout << ans << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}