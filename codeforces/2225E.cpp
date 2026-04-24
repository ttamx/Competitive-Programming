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

mt19937 rng(498623);

int rnd(int n){
    return uniform_int_distribution<int>(0,n-1)(rng);
}

void runcase(){
    int n,r;
    cin >> n >> r;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    int h=r*sqrt(3);
    while(h*h<r*r*3)h++;
    vector<int> s(h);
    for(int i=1;i<h;i++){
        s[i]=s[i-1];
        while(i*r>s[i]*h)s[i]++;
    }
    int w=2*r;
    auto check=[&](int x,int y)->pair<int,int> {
        if(x*x+y*y<=r*r)return {0,0};
        if((w-x)*(w-x)+y*y<=r*r)return {w,0};
        if((r-x)*(r-x)+(y-h)*(y-h)<=r*r)return {r,h};
        if((r+w-x)*(r+w-x)+(y-h)*(y-h)<=r*r)return {w+r,h};
        return {-1,-1};
    };
    while(true){
        int ox=rnd(w);
        int oy=rnd(h);
        int cnt=0;
        for(auto [x,y]:a){
            x-=ox,y-=oy;
            int t=y/h-(y<0&&y%h);
            x-=t*r,y-=t*h;
            x-=s[y];
            x=(x%w+w)%w;
            x+=s[y];
            if(check(x,y).first!=-1)cnt++;
        }
        if(cnt*100>=89*n){
            vector<pair<int,int>> ans;
            for(auto [x,y]:a){
                int xx=x,yy=y;
                x-=ox,y-=oy;
                int t=y/h-(y<0&&y%h);
                x-=t*r,y-=t*h;
                x-=s[y];
                x=(x%w+w)%w;
                x+=s[y];
                auto [ax,ay]=check(x,y);
                if(ax!=-1){
                    ax+=xx-x;
                    ay+=yy-y;
                    ans.eb(ax,ay);
                }
            }
            SORT(ans);
            UNI(ans);
            cout << SZ(ans) << "\n";
            for(auto [x,y]:ans){
                cout << x << " " << y << "\n";
            }
            return;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}