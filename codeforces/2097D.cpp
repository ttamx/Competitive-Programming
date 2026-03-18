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

struct Bitset{
    using u64 = uint64_t;
    int n;
    vector<u64> dat;

    Bitset(int n=0,bool x=0):n(n){
        dat.assign((n+63)>>6,x?-1:0);
        if(n)dat.back()>>=(64*(int)dat.size()-n);
    }

    struct Proxy {
        u64 &dat;
        int pos;
        Proxy(u64 &dat,int pos):dat(dat),pos(pos){}
        operator bool()const{return (dat>>pos)&1;}
        Proxy& operator=(bool x){
            if(x)dat|=(1ULL<<pos);
            else dat&=~(1ULL<<pos);
            return *this;
        }
        Proxy& operator=(const Proxy &r){
            return *this=(bool)r;
        }
    };
    Proxy operator[](int i){return Proxy(dat[i>>6],i&63);}
    bool operator[](int i)const{return (dat[i>>6]>>(i&63))&1;}

    int size(){return n;}
    void resize(int sz,bool x=0){
        dat.resize((sz+63)>>6,x?-1:0);
        int rem=sz&63;
        if(rem)dat.back()&=(1ULL<<rem)-1;
        n=sz;
    }
    void push_back(bool x){
        resize(n+1);
        (*this)[n-1]=x;
    }

    bool operator==(const Bitset &o){
        assert(n==o.n);
        for(int i=0;i<dat.size();i++)if(dat[i]!=o.dat[i])return false;
        return true;
    }
    bool operator!=(const Bitset &o){return !(*this==o);}

    Bitset &operator&=(const Bitset &o){
        assert(n==o.n);
        for(int i=0;i<dat.size();i++)dat[i]&=o.dat[i];
        return *this;
    }
    Bitset &operator|=(const Bitset &o){
        assert(n==o.n);
        for(int i=0;i<dat.size();i++)dat[i]|=o.dat[i];
        return *this;
    }
    Bitset &operator^=(const Bitset &o){
        assert(n==o.n);
        for(int i=0;i<dat.size();i++)dat[i]^=o.dat[i];
        return *this;
    }
    Bitset operator&(const Bitset &o)const{return Bitset(*this)&=o;}
    Bitset operator|(const Bitset &o)const{return Bitset(*this)|=o;}
    Bitset operator^(const Bitset &o)const{return Bitset(*this)^=o;}
};

void runcase(){
    int m;
    cin >> m;
    int n=1;
    while(m%2==0){
        n<<=1;
        m>>=1;
    }
    auto work=[&](){
        string s;
        cin >> s;
        vector<Bitset> a(n,Bitset(m));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                a[i][j]=(s[i*m+j]=='1');
            }
        }
        int rank=0;
        for(int j=0;j<m;j++){
            if(rank==n)break;
            for(int i=rank;i<n;i++){
                if(a[i][j]){
                    swap(a[rank],a[i]);
                    break;
                }
            }
            if(!a[rank][j])continue;
            for(int i=0;i<n;i++){
                if(i!=rank&&a[i][j]){
                    a[i]^=a[rank];
                }
            }
            rank++;
        }
        return a;
    };
    auto a=work(),b=work();
    for(int i=0;i<n;i++){
        if(a[i]!=b[i]){
            return void(cout << "No\n");
        }
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}