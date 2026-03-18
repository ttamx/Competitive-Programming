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

using i128 = __int128_t;

struct Info{int p,l,r;};

string i128_to_string(i128 x){
    if(x==0)return "0";
    if(x<0)return "-"+i128_to_string(-x);
    string s="";
    while(x>0){
        s.push_back('0'+x%10);
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    int p=1;
    i128 sum=a[0];
    while(n-p>=k&&(sum+a[p])*(p+1)<=sum*p)sum+=a[p++];
    vector<i128> b{0,sum},c{0,p};
    for(int i=p;i<n;i++){
        b.emplace_back(b.back()+a[i]);
        c.emplace_back(i+1);
    }
    n=b.size()-1;
    auto cost=[&](int i,int j){
        return (b[j]-b[i])*(c[j]-c[i]);
    };
    auto calc=[&](i128 lambda){
        deque<Info> dq;
        vector<pair<i128,int>> dp(n+1);
        dp[0]={0,0};
        dq.emplace_back(Info{0,1,n});
        auto f=[&](int i,int j){
            return make_pair(dp[i].first+cost(i,j)+lambda,dp[i].second+1);
        };
        for(int i=1;i<=n;i++){
            dp[i]=f(dq.front().p,i);
            if(dq.front().r==i)dq.pop_front();
            else dq.front().l++;
            while(!dq.empty()&&f(i,dq.back().l)<f(dq.back().p,dq.back().l))dq.pop_back();
            if(dq.empty())dq.emplace_back(Info{i,i+1,n});
            else{
                int l=dq.back().l,r=dq.back().r;
                while(l<r){
                    int mid=(l+r+1)/2;
                    if(f(i,mid)<f(dq.back().p,mid))r=mid-1;
                    else l=mid;
                }
                dq.back().r=l;
                if(l!=n)dq.emplace_back(Info{i,l+1,n});
            }
        }
        return dp[n];
    };
    i128 l=-1e20,r=1e20;
    while(l<r){
        i128 mid=l+(r-l)/2;
        if(calc(mid).second<=k)r=mid;
        else l=mid+1;
    }
    cout << i128_to_string(calc(l).first-l*k) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}