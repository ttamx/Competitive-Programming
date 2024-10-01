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

struct Point{
    ll x,y;
    Point(ll _x,ll _y):x(_x),y(_y){}
    friend Point operator-(const Point &lhs,const Point &rhs){
        return Point(lhs.x-rhs.x,lhs.y-rhs.y);
    }
    bool operator<(const Point &o)const{
        return x<o.x||(x==o.x&&y<o.y);
    }
};

struct Line{
    Point p1,p2;
    Line(Point _p1,Point _p2):p1(_p1),p2(_p2){}
};

ll cross(Point p1,Point p2){
    return p1.x*p2.y-p2.x*p1.y;
}

ll cross(Point p1,Point p2,Point o){
    return cross(p1-o,p2-o);
}

int sgn(ll x){
    return x<0?-1:x>0?1:0;
}

void runcase(){
    int n;
    cin >> n;
    vector<Line> v;
    ll ans=0;
    for(int i=0;i<n;i++){
        ll x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ll dx=abs(x1-x2);
        ll dy=abs(y1-y2);
        ans+=gcd(dx,dy)+1;
        v.emplace_back(Line(Point(x1,y1),Point(x2,y2)));
    }
    map<Point,int> cnt;
    for(int i=0;i<n;i++){
        Point a=v[i].p1,b=v[i].p2;
        for(int j=0;j<i;j++){
            Point c=v[j].p1,d=v[j].p2;
	        ll oa=cross(d,a,c),ob=cross(d,b,c);
	        ll oc=cross(b,c,a),od=cross(b,d,a);
	        if(sgn(oa)*sgn(ob)<=0&&sgn(oc)*sgn(od)<=0){
                ll x=a.x*ob-b.x*oa;
                ll y=a.y*ob-b.y*oa;
                ll div=ob-oa;
                if(x%div==0&&y%div==0){
                    cnt[Point(x/div,y/div)]++;
                }
            }
        }
    }
    vector<int> dp(n+1);
    for(int i=1;i<=n;i++){
        dp[i]=i*(i-1)/2;
    }
    for(auto [_,x]:cnt){
        ans-=lower_bound(dp.begin(),dp.end(),x)-dp.begin()-1;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}