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
    string s;
    cin >> s;
    for(int i=0;i<n;i++){
        if(s[i]=='B'&&s[(i+1)%n]=='B'){
            for(auto &x:s){
                x=(x=='R'?'B':'R');
            }
            break;
        }
    }
    for(int i=0;i<n;i++){
        if(s[i]=='B'&&s[(i+1)%n]=='B'){
            cout << "NO\n";
            return;
        }
    }
    if(s==string(n,'R')){
        cout << "YES\n";
        return;
    }
    for(int i=0;i<n;i++){
        if(s[i]=='B'){
            rotate(s.begin(),s.begin()+i,s.end());
            break;
        }
    }
    int cnt=0;
    int block=0;
    for(int i=1;i<n;i++){
        block++;
        int j=i;
        while(j<n&&s[j]=='R'){
            j++;
        }
        if((j-i)%2==0){
            cnt++;
        }
        i=j;
    }
    if(block==1){
        cout << "YES\n";
    }else if(cnt==0){
        cout << (n%2==1?"YES":"NO") << "\n";
    }else{
        cout << (cnt==1?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}