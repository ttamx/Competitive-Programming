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

void runcase_encode(){
    int n,c;
    cin >> n >> c;
    vector<string> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        for(int j=0;j<n;j++){
            b[j]+=a[i][j];
        }
    }
    if(c){
        int x=min_element(a.begin(),a.end())-a.begin();
        int y=max_element(b.begin(),b.end())-b.begin();
        assert(a[x]<=b[y]);
        cout << x+1 << " " << y+1 << "\n";
    }else{
        int x=max_element(a.begin(),a.end())-a.begin();
        int y=min_element(b.begin(),b.end())-b.begin();
        assert(a[x]>b[y]);
        cout << x+1 << " " << y+1 << "\n";
    }
}

void runcase_decode(){
    int n;
    string a,b;
    cin >> n >> a >> b;
    cout << (a<=b) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int t(1);
    cin >> t;
    if(s[0]=='f'){
        while(t--)runcase_encode();
    }else{
        while(t--)runcase_decode();
    }
}