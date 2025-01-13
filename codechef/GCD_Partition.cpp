#include "template.hpp"
#include "data-structure/sparse-table.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

struct Monoid{
    using value_type = int;
    static int op(const int &x,const int &y){
        return gcd(x,y);
    }
    static int unit(){
        return 0;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    a.insert(a.begin(),1);
    SparseTable<Monoid> st(a);
    vector<map<int,mint>> dp(n+1);
    mint ans=0;
    for(int i=1;i<=n;i++){
        for(auto [x,v]:dp[i-1]){
            if(v!=0){
                dp[i][x]+=v;
            }
        }
        vector<tuple<int,int,int>> cand;
        for(int j=i;j<=n;j++){
            int val=st.query(i,j);
            int l=j,r=n;
            while(l<r){
                int m=(l+r+1)/2;
                if(st.query(i,m)==val)l=m;
                else r=m-1;
            }
            cand.emplace_back(val,j,l);
            j=l;
        }
        for(auto [v,l,r]:cand){
            if(v>1&&!dp[i-1].count(v-1))continue;
            mint val=v>1?dp[i-1][v-1]:mint(1);
            dp[l][v]+=val;
            if(r<n){
                dp[r+1][v]-=val;
            }
        }
        for(auto [_,v]:dp[i]){
            ans+=v;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}