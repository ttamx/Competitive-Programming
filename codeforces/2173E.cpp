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

const bool LOCAL=false;

void runcase(){
    int n=9;
    if(!LOCAL){
        cin >> n;
    }
    vector<int> a(n),pos(n);
    if(LOCAL){
        iota(a.begin(),a.end(),0);
        shuffle(a.begin(),a.end(),rng);
        for(auto x:a){
            cerr << x << " ";
        }
        cerr << "\n";
    }else{
        for(auto &x:a){
            cin >> x;
            x--;
        }
    }
    for(int i=0;i<n;i++){
        pos[a[i]]=i;
    }
    int cnt=0;
    auto work=[&](int u,int v){
        int x,y;
        if(LOCAL){
            if(rng()&1){
                x=n-u-1;
                y=n-v-1;
            }else{
                x=u;
                y=v;
            }
            cnt++;
        }else{
            cout << "? " << u+1 << " " << v+1 << endl;
            if(u>v)swap(u,v);
            cin >> x >> y;
            x--,y--;
        }
        swap(a[x],a[y]);
        swap(pos[a[x]],pos[a[y]]);
    };
    int mid=n/2;
    if(n%2==1){
        while(pos[mid]!=mid){
            work(pos[mid],mid);
        }
    }
    for(int i=0;i<mid;i++){
        int j=n-i-1;
        if(pos[i]+pos[j]!=n-1){
            work(pos[i],n-pos[j]-1);
        }
        assert(pos[i]+pos[j]==n-1);
        int p=pos[i];
        while(pos[i]!=i||pos[j]!=j){
            work(i,p);
        }
    }
    if(LOCAL){
        cerr << "n = " << n << " q = " << cnt << "\n";
        for(int i=0;i<n;i++){
            if(a[i]!=i){
                assert(false);
            }
        }
        return;
    }
    cout << "!" << endl;
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}