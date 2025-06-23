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
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<pair<int,int>> ans;
    auto work=[&](int op,int i){
        ans.emplace_back(op,i);
        if(op==1)swap(a[i],a[i+1]);
        if(op==2)swap(b[i],b[i+1]);
        if(op==3)swap(a[i],b[i]);
    };
    for(int i=1;i<=2*n-2;i++){
        int pos=(i-1)/2;
        for(int j=0;j<n;j++){
            if(a[j]==i){
                for(int k=j;k<pos+1;k++){
                    work(1,k);
                }
                for(int k=j;k>pos+1;k--){
                    work(1,k-1);
                }
                if(i%2==0){
                    work(3,pos+1);
                    work(2,pos);
                }else{
                    work(1,pos);
                }
                break;
            }
            if(b[j]==i){
                for(int k=j;k<pos+1;k++){
                    work(2,k);
                }
                for(int k=j;k>pos+1;k--){
                    work(2,k-1);
                }
                if(i%2==1){
                    work(3,pos+1);
                    work(1,pos);
                }else{
                    work(2,pos);
                }
                break;
            }
        }
    }
    if(a.back()==2*n)work(3,n-1);
    // for(auto x:a)cerr << x << " ";
    // cerr << "\n";
    // for(auto x:b)cerr << x << " ";
    // cerr << "\n";
    cout << ans.size() << "\n";
    for(auto [x,y]:ans){
        cout << x << " " << y+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // for(int i=40;i>=1;i--){
    //     cout << i*2 << " ";
    // }
    // cout << "\n";
    // for(int i=40;i>=1;i--){
    //     cout << i*2-1 << " ";
    // }
    // cout << "\n";
    int t(1);
    cin >> t;
    while(t--)runcase();
}