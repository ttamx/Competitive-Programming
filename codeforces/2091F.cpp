#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m,d;
    cin >> n >> m >> d;
    int d2=0;
    while((d2+1)*(d2+1)+1<=d*d)d2++;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<mint> dp(m);
    for(int i=0;i<m;i++){
        if(a.back()[i]=='X'){
            dp[i]=1;
        }
    }
    auto work=[&](int dd,const string &str){
        vector<mint> ndp(m);
        for(int i=0;i<m;i++){
            ndp[max(0,i-dd)]+=dp[i];
            if(i+dd+1<m)ndp[i+dd+1]-=dp[i];
        }
        for(int i=1;i<m;i++)ndp[i]+=ndp[i-1];
        dp=move(ndp);
        for(int i=0;i<m;i++){
            if(str[i]=='#'){
                dp[i]=0;
            }
        }
    };
    work(d,a.back());
    a.pop_back();
    reverse(a.begin(),a.end());
    for(auto &s:a){
        work(d2,s);
        work(d,s);
    }
    cout << accumulate(dp.begin(),dp.end(),mint(0)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}