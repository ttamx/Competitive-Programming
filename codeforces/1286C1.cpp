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
    auto ask=[&](int l,int r){
        if(l>r){
            return vector<string>{};
        }
        cout << "? " << l << " " << r << endl;
        int sz=(r-l+1)*(r-l+2)/2;
        vector<string> a;
        for(int i=0;i<sz;i++){
            string s;
            cin >> s;
            sort(s.begin(),s.end());
            a.emplace_back(s);
        }
        sort(a.begin(),a.end());
        return a;
    };
    auto a=ask(1,n),b=ask(2,n);
    vector<string> c;
    int pos=0;
    for(auto x:a){
        if(pos<b.size()&&x==b[pos]){
            pos++;
        }else{
            c.emplace_back(x);
        }
    }
    sort(c.begin(),c.end(),[&](string x,string y){
        return x.size()<y.size();
    });
    string pre="";
    string ans="";
    for(auto x:c){
        int p=0;
        for(auto e:x){
            if(p<pre.size()&&e==pre[p]){
                p++;
            }else{
                ans.push_back(e);
            }
        }
        pre=x;
    }
    cout << "! " << ans << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}