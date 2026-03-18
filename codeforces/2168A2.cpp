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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string phase;
    cin >> phase;
    if(phase[0]=='f'){
        int n;
        cin >> n;
        string s="";
        for(int i=0;i<n;i++){
            int x;
            cin >> x;
            for(int j=0;j<10;j++){
                s.push_back('a'+x%26);
                x/=26;
            }
        }
        cout << s << "\n";
    }else{
        string s;
        cin >> s;
        cout << s.size()/10 << "\n";
        for(int i=0;i<s.size();i+=10){
            int x=0;
            for(int j=9;j>=0;j--){
                x=x*26+s[i+j]-'a';
            }
            cout << x << " ";
        }
        cout << "\n";
    }
}