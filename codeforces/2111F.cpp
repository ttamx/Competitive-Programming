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

const int K=50000;

void runcase(){
    ll pp,ss;
    cin >> pp >> ss;
    ll g=gcd(pp,ss);
    pp/=g,ss/=g;
    for(ll p=pp,s=ss;s<=K;p+=pp,s+=ss){
        if(p%4)continue;
        ll h=p/4;
        ll w=h;
        if(h+w-1<=s&&s<=h*w){
            cout << s << "\n";
            for(int i=0;i<w;i++){
                cout << 0 << " " << i << "\n";
                s--;
            }
            for(int i=1;i<h;i++){
                cout << i << " " << 0 << "\n";
                s--;
            }
            assert(s>=0);
            for(int i=1;i<h;i++){
                if(s==0)break;
                for(int j=1;j<w;j++){
                    if(s==0)break;
                    s--;
                    cout << i << " " << j << "\n";
                }
            }
            return;
        }
    }
    for(ll p=pp,s=ss;s<=K;p+=pp,s+=ss){
        if(p%4!=2)continue;
        ll h=p/4;
        ll w=h+1;
        if(h+w-1<=s&&s<=h*w){
            cout << s << "\n";
            for(int i=0;i<w;i++){
                cout << 0 << " " << i << "\n";
                s--;
            }
            for(int i=1;i<h;i++){
                cout << i << " " << 0 << "\n";
                s--;
            }
            assert(s>=0);
            for(int i=1;i<h;i++){
                if(s==0)break;
                for(int j=1;j<w;j++){
                    if(s==0)break;
                    s--;
                    cout << i << " " << j << "\n";
                }
            }
            return;
        }
    }
    cout << -1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}