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
    vector<int> a(n+1);
    int one=n+1,cnt=0;
    set<int> s;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]==1){
            one=min(one,i);
        }
        if(a[i]==-1){
            s.emplace(i);
        }
    }
    if(a[1]==-1){
        a[1]=1;
        one=1;
        s.erase(1);
    }
    bool need=false;
    for(int i=1;i<=n;i++){
        if(a[i]==-1){
            if(one>n&&s.size()==1){
                if(need){
                    a[i]=1;
                    one=min(one,i);
                }else{
                    pair<int,int> best(i,i);
                    for(int j=1;j<=n;j++){
                        if(i!=j){
                            assert(a[j]>=1);
                            best=min(best,make_pair(a[j],j));
                        }
                    }
                    a[i]=best.second;
                }
            }else{
                a[i]=-2;
                need=true;
            }
            s.erase(i);
        }else if(a[a[i]]==-1){
            a[a[i]]=1;
            one=min(one,a[i]);
            s.erase(a[i]);
        }else if(a[a[i]]==-2){
            if(!s.empty()&&*s.begin()<one){
                one=*s.begin();
                s.erase(one);
                a[one]=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i]==-2){
            assert(one<=n);
            a[i]=one;
        }
        assert(a[i]>=1);
    }
    for(int i=1;i<=n;i++){
        cout << a[a[i]] << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}