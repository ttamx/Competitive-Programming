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
    int n,k;
    cin >> n >> k;
    k--;
    vector<int> a(n);
    vector<vector<int>> pos(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        a[i]--;
        pos[a[i]].emplace_back(i);
    }
    int cnt=0;
    vector<int> t(n);
    vector<int> cand;
    for(int i=0;i<n;i++){
        if(pos[i].size()<=k){
            for(auto j:pos[i]){
                t[j]=1;
                cnt++;
            }
            k-=pos[i].size();
        }else{
            for(auto j:pos[i]){
                t[j]=2;
            }
            break;
        }
    }
    int l=0,r=n-1;
    while(l<r&&cnt>0){
        while(l<n&&t[l]==0)l++;
        while(r>=0&&t[r]==0)r--;
        if(l>r)break;
        if(t[l]==2&&t[r]==2){
            k-=2;
            l++,r--;
        }else if(t[l]==2){
            l++;
        }else if(t[r]==2){
            r--;
        }else{
            if(a[l]!=a[r]){ 
                cout << "NO\n";
                return;
            }
            cnt-=2;
            l++,r--;
        }
    }
    if(cnt>1){
        cout << "NO\n";
        return;
    }
    if(cnt==0){
        while(l<=r){
            if(t[l]==2){
                k--;
            }
            l++;
        }
    }
    cout << (k<=0?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}