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

const int B=20;

struct Gauss{
    int tot;
    vector<int> basis;
    Gauss(){init();}
    void init(){
        tot=0;
        basis.assign(B,0);
    }
    bool check(int x){
        for(int i=B-1;i>=0;i--){
            if(x>>i&1){
                if(!basis[i]){
                    return true;
                }else{
                    x^=basis[i];
                }
            }
        }
        return false;
    }
    bool insert(int x){
        for(int i=B-1;i>=0;i--){
            if(x>>i&1){
                if(!basis[i]){
                    basis[i]=x;
                    tot++;
                    return true;
                }else{
                    x^=basis[i];
                }
            }
        }
        return false;
    }
    int count(int x){
        int res=0,v=0,cnt=tot;
        for(int i=B-1;i>=0;i--){
            if(basis[i]){
                cnt--;
                if(x>>i&1){
                    res+=1<<cnt;
                    if(!(v>>i&1)){
                        v^=basis[i];
                    }
                }else if(v>>i&1){
                    v^=basis[i];
                }
            }else if((x>>i&1)!=(v>>i&1)){
                if((x>>i&1)>(v>>i&1)){
                    res+=1<<cnt;
                }
                break;
            }
        }
        return res;
    }
    int find(int k){
        int v=0,cnt=tot;
        for(int i=B-1;i>=0;i--){
            if(basis[i]){
                cnt--;
                if(k>=(1<<cnt)){
                    k-=1<<cnt;
                    if(!(v>>i&1)){
                        v^=basis[i];
                    }
                }else if(v>>i&1){
                    v^=basis[i];
                }
            }
        }
        assert(k==0);
        return v;
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> pos,b(n);
    for(int i=n-1;i>=0;i--){
        vector<int> cands{i};
        swap(pos,cands);
        int val=0;
        int last=i+1;
        int ord=0;
        Gauss ds;
        ds.insert(a[i]);
        int pre=i;
        bool bad=false;
        b[i]=i+1;
        for(auto j:cands){
            if(!ds.check(a[j]))continue;
            if(last+1<j)break;
            val=ds.find(ord+j-pre-1);
            pos.emplace_back(j);
            ds.insert(a[j]);
            ord=ds.count(val)+1;
            if(ord>=(1<<pos.size()))break;
            last=j+(1<<pos.size())-ord-1;
            pre=j;
        }
        for(auto j:cands){
            if(!ds.check(a[j]))continue;
            pos.emplace_back(j);
            ds.insert(a[j]);
        }
        b[i]=last;
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        cout << (b[l]>=r?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}