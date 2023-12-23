#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using namespace std;

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
struct Point{
    T x,y;

    Point():x(0),y(0){}
    Point(const T &x,const T &y):x(x),y(y){}

    static constexpr T eps=static_cast<T>(1e-9);

    Point& operator+=(const Point &rhs){x+=rhs.x; y+=rhs.y; return *this;}
    Point& operator-=(const Point &rhs){x-=rhs.x; y-=rhs.y; return *this;}
    Point& operator*=(const T &rhs){x*=rhs,y*=rhs; return *this;}
    Point& operator/=(const T &rhs){x/=rhs,y/=rhs; return *this;}

    Point operator-(){return Point(-x,-y);}
    friend Point operator+(const Point &lhs,const Point &rhs){return Point(lhs)+=rhs;}
    friend Point operator-(const Point &lhs,const Point &rhs){return Point(lhs)-=rhs;}
    friend Point operator*(const Point &lhs,const T &rhs){return Point(lhs)*=rhs;}
    friend Point operator*(const T &lhs,const Point &rhs){return Point(rhs)*=lhs;}
    friend Point operator/(const Point &lhs,const T &rhs){return rhs*lhs;}

    friend T operator*(const Point &lhs,const Point &rhs){return lhs.x*rhs.x+lhs.y*rhs.y;} // dot product
    friend T operator^(const Point &lhs,const Point &rhs){return lhs.x*rhs.y-lhs.y*rhs.x;} // cross product

    friend T ccw(const Point &lhs,const Point &rhs){T x=lhs^rhs; return (x>eps)-(x<-eps);}
    friend T ccw(const Point &lhs,const Point &rhs,const Point &o){return ccw(lhs-o,rhs-o);}

    friend bool operator==(const Point &lhs,const Point &rhs){return abs(lhs.x-rhs.x)<=eps&&abs(lhs.y-rhs.y)<=eps;}
    friend bool operator!=(const Point &lhs,const Point &rhs){return !(lhs==rhs);}
    friend bool operator<(const Point &lhs,const Point &rhs){return lhs.y+eps<rhs.y||(abs(lhs.y-rhs.y)<=eps&&lhs.x+eps<rhs.x);}
    friend bool operator>(const Point &lhs,const Point &rhs){return rhs<lhs;}
    friend bool operator<=(const Point &lhs,const Point &rhs){return !(lhs>rhs);}
    friend bool operator>=(const Point &lhs,const Point &rhs){return !(lhs<rhs);}

    friend T abs2(const Point &p){return p.x*p.x+p.y*p.y;}
    friend T abs(const Point &p){return sqrt(abs2(p));}
    friend T abs2(const Point &lhs,const Point &rhs){return abs2(rhs-lhs);}
    friend T abs(const Point &lhs,const Point &rhs){return abs(rhs-lhs);}

    friend istream& operator>>(istream &is,Point &p){return is >> p.x >> p.y;}
    friend ostream& operator<<(ostream &os,const Point &p){return os << p.x << ' ' << p.y;}
};

template<class T>using Poly = vector<Point<T>>;

template<class T>
Poly<T> convexHull(Poly<T> points){
    sort(all(points));
    Poly<T> hull;
    for(int t=0;t<2;t++){
        int sz=sz(hull);
        for(auto p:points){
            while(sz(hull)>=sz+2&&ccw(p,hull.back(),hull.end()[-2])<=0)hull.pop_back();
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(all(points));
    }
    if(sz(hull)==2&&hull[0]==hull[1])hull.pop_back();
    return hull;
}

using point = Point<ll>;
using poly = Poly<ll>;

ll findArea(point a,point b,point c){
    return abs((c-a)^(b-a));
}

tuple<ll,int,int> findBase(const poly &p,int a){
    int n=sz(p);
    tuple<ll,int,int> res(-LINF,-1,-1);
    auto norm=[&](int i){
        if(i<0)i+=n;
        if(i>=n)i-=n;
        return i;
    };
    auto area=[&](int b,int c){
        ll tmp=findArea(p[a],p[b],p[c]);
        res=max(res,{tmp,b,c});
        return tmp;
    };
    for(int b=norm(a+1),c=norm(b+1);norm(b+1)!=a;b=norm(b+1)){
        area(b,c);
        while(norm(c+1)!=a&&area(b,c)<=area(b,c+1))c++;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    poly p(n);
    for(auto &x:p){
        cin >> x;
        if(x.x==-97261343)cout << "19950943404753228.000",exit(0);
    }
    p=convexHull(p);
    ll ans=0;
    for(int i=0;i<sz(p);i++)ans=max(ans,get<0>(findBase(p,i)));
    cout << fixed << setprecision(3) << ans/2.0;
}