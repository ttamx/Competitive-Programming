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
    string s;
    cin >> s;
    int n=s.size();
    vector<bool> alive(n,true);
    vector<int> l(n),r(n);
    vector<int> del;
    for(int i=0;i<n;i++){
        l[i]=r[i]=i;
    }
    auto work=[&](int i){
        if(i>0){
            int p=l[i-1];
            if(alive[p]){
                if(s[p]!=s[i]){
                    del.emplace_back(i);
                }
            }else if(p>0){
                p--;
                assert(alive[p]);
                if(s[p]!=s[i]){
                    del.emplace_back(i);
                }
            }
        }
        if(i+1<n){
            int p=r[i+1];
            if(alive[p]){
                if(s[p]!=s[i]){
                    del.emplace_back(i);
                }
            }else if(p+1<n){
                p++;
                assert(alive[p]);
                if(s[p]!=s[i]){
                    del.emplace_back(i);
                }
            }
        }
    };
    for(int i=0;i<n;i++){
        work(i);
    }
    for(int t=0;;t++){
        if(del.empty()){
            cout << t << "\n";
            break;
        }
        vector<int> pos;
        for(auto i:del){
            if(!alive[i])continue;
            alive[i]=false;
            if(i>0){
                int p=l[i-1];
                if(alive[p]){
                    pos.emplace_back(p);
                }else if(p>0){
                    p--;
                    assert(alive[p]);
                    pos.emplace_back(p);
                }
                if(!alive[i-1]){
                    r[l[i-1]]=r[i];
                    l[r[i]]=l[i-1];
                }
            }
            if(i+1<n){
                int p=r[i+1];
                if(alive[p]){
                    pos.emplace_back(p);
                }else if(p+1<n){
                    p++;
                    assert(alive[p]);
                    pos.emplace_back(p);
                }
                if(!alive[i+1]){
                    l[r[i+1]]=l[i];
                    r[l[i]]=r[i+1];
                }
            }
        }
        del.clear();
        for(auto i:pos){
            if(alive[i]){
                work(i);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}