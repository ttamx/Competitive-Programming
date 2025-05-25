#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(i&1){
            a[i]=-a[i];
        }
    }
    for(int i=1;i<=n;i++){
        a[i]+=a[i-1];
    }
    vector<pair<ll,ll>> st1,st2;
    mint ans=0,sum1=0,sum2=0;
    for(int i=0;i<=n;i++){
        ll cnt=1;
        while(!st1.empty()&&st1.back().first<a[i]){
            auto [h,c]=st1.back();
            st1.pop_back();
            sum1-=mint(h)*c;
            cnt+=c;
        }
        st1.emplace_back(a[i],cnt);
        sum1+=mint(a[i])*cnt;
        cnt=1;
        while(!st2.empty()&&st2.back().first>a[i]){
            auto [h,c]=st2.back();
            st2.pop_back();
            sum2-=mint(h)*c;
            cnt+=c;
        }
        st2.emplace_back(a[i],cnt);
        sum2+=mint(a[i])*cnt;
        ans+=sum1-sum2;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}