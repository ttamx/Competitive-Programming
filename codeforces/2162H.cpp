#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> cnt(n+1);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<pair<int,int>> a(m),b;
    for(auto &[l,r]:a){
        cin >> l >> r;
    }
    sort(a.begin(),a.end());
    for(auto [l,r]:a){
        if(!b.empty()&&b.back().first==l){
            b.pop_back();
        }
        if(b.empty()||r>b.back().second){
            b.emplace_back(l,r);
        }
    }
    m=b.size();
    vector<int> dp(n+1,-INF);
    dp[0]=0;
    int last=0;
    auto fill_gap=[&](int cur){
        int gap=cur-last-1;
        for(int j=0;j<gap;j++){
            auto ndp=dp;
            for(int k=n-1;k>=0;k--){
                ndp[k]=max(ndp[k],dp[k]+1);
            }
            for(int k=n-1;k>=0;k--){
                ndp[k+1]=max(ndp[k+1],dp[k]);
            }
            dp=move(ndp);
            for(int i=n-1;i>=0;i--){
                dp[i]=max(dp[i],dp[i+1]);
            }
        }
    };
    for(int i=0;i<m;i++){
        auto [l,r]=b[i];
        fill_gap(l);
        vector<pair<int,int>> cands,vec,good;
        int j=i;
        while(j+1<m&&b[j+1].first<=r){
            vec.emplace_back(b[j+1].first,r);
            r=b[j+1].second;
            j++;
        }
        cands.emplace_back(0,r-l+1);
        for(auto [x,y]:vec){
            cands.emplace_back(minmax(x-l,r-y));
        }
        for(int ii=0;ii<vec.size();ii++){
            for(int jj=ii+1;jj<vec.size();jj++){
                if(vec[ii].second<vec[jj].first){
                    cands.emplace_back(minmax(vec[ii].first-l+r-vec[jj].second,vec[jj].first-vec[ii].second-1));
                }
            }
        }
        sort(cands.begin(),cands.end());
        for(auto [x,y]:cands){
            while(!good.empty()&&good.back().second<=y){
                good.pop_back();
            }
            good.emplace_back(x,y);
        }
        auto ndp=dp;
        for(auto [x,y]:good){
            for(int k=n-x;k>=0;k--){
                ndp[k+x]=max(ndp[k+x],dp[k]+y);
            }
            for(int k=n-y;k>=0;k--){
                ndp[k+y]=max(ndp[k+y],dp[k]+x);
            }
        }
        dp=move(ndp);
        for(int i=n-1;i>=0;i--){
            dp[i]=max(dp[i],dp[i+1]);
        }
        i=j;
        last=r;
    }
    fill_gap(n+1);
    string ans(n,'0');
    int c0=0,c1=n;
    for(int i=1;i<=n;i++){
        c1-=cnt[i];
        if(c1<=dp[c0]||c0<=dp[c1]){
            ans[i-1]='1';
        }
        c0+=cnt[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}