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
    int n;
    cin >> n;
    auto work=[&](string &s){
        vector<pair<int,int>> a;
        auto push=[&](int l,int r){
            a.emplace_back(l,r);
            for(int i=l;i<=r;i++){
                s[i]^=1;
            }
        };
        int l=-1,r=-1;
        for(int i=0;i+1<n;i++){
            if(s[i]==s[i+1]){
                l=r=i;
                break;
            }
        }
        if(l==-1){
            push(0,2);
            l=r=2;
        }
        while(true){
            bool ok=false;
            while(r+1<n&&s[r+1]==s[r]){
                ok=true;
                r++;
            }
            while(l-1<n&&s[l-1]==s[l]){
                ok=true;
                l--;
            }
            if(!ok)break;
            push(l,r);
        }
        return a;
    };
    string s,t;
    cin >> s >> t;
    auto a=work(s);
    auto b=work(t);
    if(s!=t){
        a.emplace_back(0,n-1);
    }
    reverse(b.begin(),b.end());
    a.insert(a.end(),b.begin(),b.end());
    cout << a.size() << "\n";
    for(auto [l,r]:a){
        cout << l+1 << " " << r+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}