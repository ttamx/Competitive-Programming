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

const int X=6e6;
const int N=4e5+5;

int cnt=1;
ll val[N];

vector<int> prime;
bool is_composite[X];

void sieve (int n) {
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]){
            prime.push_back(i);
            val[cnt]=val[cnt-1]+i;
            cnt++;
            if(cnt>=N)break;
        }
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    ll s=0;
    for(auto &x:a){
        cin >> x;
        s+=x;
    }
    sort(a.rbegin(),a.rend());
    int ans=0;
    while(n>1&&s<val[n]){
        n--;
        s-=a[n];
        ans++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    sieve(X);
    int t(1);
    cin >> t;
    while(t--)runcase();
}