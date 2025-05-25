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
    string s,t;
    cin >> s >> t;
    if(count(s.begin(),s.end(),'1')!=count(t.begin(),t.end(),'1')){
        cout << -1 << "\n";
        return;
    }
    auto compress=[&](const string &str){
        deque<pair<int,char>> dq;
        for(auto x:str){
            if(!dq.empty()&&x==dq.back().second){
                dq.back().first++;
            }else{
                dq.emplace_back(1,x);
            }
        }
        return dq;
    };
    auto a=compress(s);
    auto b=compress(t);
    int ans=0;
    for(auto [c,x]:b){
        int cnt=0;
        int diff=0;
        while(!a.empty()&&cnt<c){
            if(a.front().second==x){
                cnt+=a.front().first;
            }else{
                diff+=a.front().first;
                ans++;
            }
            a.pop_front();
        }
        if(cnt!=c){
            cout << -1 << "\n";
            return;
        }
        if(diff){
            if(!a.empty()&&a.front().second!=x){
                a.front().first+=diff;
            }else{
                a.emplace_back(diff,x^1);
            }
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