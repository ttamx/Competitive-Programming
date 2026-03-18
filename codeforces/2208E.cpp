#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

inline vector<mint> conv(const vector<mint> &a,const vector<mint> &b){
    assert(!a.empty()&&!b.empty());
    int n=a.size();
    int m=b.size();
    vector<mint> c(n+m-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            c[i+j]+=a[i]*b[j];
        }
    }
    return c;
}

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        if(a[i]>=i){
            cout << 0 << "\n";
            return;
        }
    }
    a.emplace_back(0);
    vector<pair<int,vector<mint>>> st;
    st.emplace_back(0,vector<mint>{});
    for(int i=1;i<=n+1;i++){
        if(a[i]==-1){
            st.emplace_back(i,vector<mint>{});
        }else{
            vector<vector<mint>> cur;
            while(!st.empty()&&st.back().first!=a[i]){
                cur.emplace_back(move(st.back().second));
                st.pop_back();
            }
            if(st.empty()){
                cout << 0 << "\n";
                return;
            }
            reverse(cur.begin(),cur.end());
            vector<mint> dp{1};
            for(auto &e:cur){
                if(e.empty()){
                    mint tot=0;
                    dp.emplace_back(0);
                    for(int i=dp.size()-1;i>=1;i--){
                        tot+=dp[i-1];
                        dp[i]=tot;
                    }
                    dp[0]=0;
                }else{
                    dp=conv(dp,e);
                }
            }
            mint ways=0;
            for(auto x:dp)ways+=x;
            st.emplace_back(i,vector<mint>{0,ways});
        }
    }
    cout << st.back().second[1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}