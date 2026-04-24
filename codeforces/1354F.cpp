#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define SORT(a) sort(ALL(a))
#define RSORT(a) sort(RALL(a))
#define REV(a) reverse(ALL(a))
#define UNI(a) a.erase(unique(ALL(a)),a.end())
#define SZ(a) (int)(a.size())
#define LB(a,x) (int)(lower_bound(ALL(a),x)-a.begin())
#define UB(a,x) (int)(upper_bound(ALL(a),x)-a.begin())
#define MIN(a) *min_element(ALL(a))
#define MAX(a) *max_element(ALL(a))

using ll = long long;
using db = long double;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;

const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/4;
const db DINF=numeric_limits<db>::infinity();
const int MOD=998244353;
const int MOD2=1000000007;
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using PQ = priority_queue<T,vector<T>,greater<T>>;

#define vv(T,a,n,...) vector<vector<T>> a(n,vector<T>(__VA_ARGS__))
#define vvv(T,a,n,m,...) vector<vector<vector<T>>> a(n,vector<vector<T>>(m,vector<T>(__VA_ARGS__)))
#define vvvv(T,a,n,m,k,...) vector<vector<vector<vector<T>>>> a(n,vector<vector<vector<T>>>(m,vector<vector<T>>(k,vector<T>(__VA_ARGS__))))

template<class T,class U>
bool chmin(T &a,U b){return b<a?a=b,1:0;}
template<class T,class U>
bool chmax(T &a,U b){return a<b?a=b,1:0;}
template<class T,class U>
T SUM(const U &a){return accumulate(ALL(a),T{});}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];;
    }
    int opt=-1;
    vector<int> ans;
    vector<int> ord(n);
    iota(ALL(ord),0);
    shuffle(ALL(ord),rng);
    for(int t=2e5;t>0;t--){
        int i=rng()%n,j=rng()%n;
        while(i==j)i=rng()%n,j=rng()%n;
        swap(ord[i],ord[j]);
        int sum=0,lz=0;
        PQ<int> pq;
        bool ok=false;
        for(int i=0;i<n;i++){
            int j=ord[i];
            if(SZ(pq)==k){
                sum-=pq.top();
                pq.pop();
            }
            lz+=b[j];
            sum+=a[j]-lz;
            pq.emplace(a[j]-lz);
            int res=sum+lz*SZ(pq);
            if(res>opt){
                ok=true;
                opt=res;
                ans=vector<int>(ord.begin(),ord.begin()+i+1);
            }
        }
        if(!ok)swap(ord[i],ord[j]);
    }
    vector<int> out;
    PQ<pair<int,int>> pq;
    int lz=0;
    for(auto i:ans){
        if(SZ(pq)==k){
            out.eb(-pq.top().second-1);
            pq.pop();
        }
        lz+=b[i];
        pq.emplace(a[i]-lz,i);
        out.eb(i+1);
    }
    cout << SZ(out) << "\n";
    for(auto i:out){
        cout << i << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}