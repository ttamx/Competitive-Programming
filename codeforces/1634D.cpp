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
    auto ask=[&](int i,int j,int k){
        cout << "? " << i << " " << j << " " << k << endl;
        int res;
        cin >> res;
        return res;
    };
    int n;
    cin >> n;
    int cur=ask(1,2,3);
    int best=3;
    for(int i=4;i<=n;i++){
        int tmp=ask(1,2,i);
        if(tmp>cur){
            cur=tmp;
            best=i;
        }
    }
    int cnt=0;
    int best2=2;
    int best3=-1;
    for(int i=3;i<=n;i++){
        if(i==best){
            continue;
        }
        cnt++;
        if(cnt<=n-4){
            int tmp=ask(1,best,i);
            if(tmp>cur){
                cur=tmp;
                best2=i;
            }
        }else{
            best3=i;
        }
    }
    int val1=ask(best,best2,best3);
    int val2=ask(1,best2,best3);
    int val3=ask(best,1,best3);
    int val4=ask(best,best2,1);
    int mx=max({val1,val2,val3,val4});
    auto answer=[&](int i,int j){
        cout << "! " << i << " " << j << endl;
    };
    if(val1==mx&&val2==mx){
        answer(best2,best3);
    }else if(val1==mx&&val3==mx){
        answer(best,best3);
    }else if(val1==mx&&val4==mx){
        answer(best,best2);
    }else if(val2==mx&&val3==mx){
        answer(1,best3);
    }else if(val2==mx&&val4==mx){
        answer(1,best2);
    }else if(val3==mx&&val4==mx){
        answer(1,best);
    }else{
        assert(false);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}