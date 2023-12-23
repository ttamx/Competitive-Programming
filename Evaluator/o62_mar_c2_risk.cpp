#include<bits/stdc++.h>

using namespace std;

template<class T>
struct Point{
    T x,y;

    Point():x(0),y(0){}
    Point(const T &x,const T &y):x(x),y(y){}

    static constexpr T eps=static_cast<T>(0);

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
    sort(points.begin(),points.end());
    Poly<T> hull;
    for(int t=0;t<2;t++){
        int sz=hull.size();
        for(auto p:points){
            while(hull.size()>=sz+2&&ccw(p,hull.back(),hull.end()[-2])<=0)hull.pop_back();
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(points.begin(),points.end());
    }
    if(hull.size()==2&&hull[0]==hull[1])hull.pop_back();
    return hull;
}

template<class T>
int isInside(const Point<T> &point,const Poly<T> &poly,int top){
    if(point<poly[0]||point>poly[top])return 1;
    int dir=ccw(point,poly[top],poly[0]);
    if(dir==0){
        if(point==poly[0]||point==poly[top])return 0;
        return top==1||top==poly.size()-1?0:-1;
    }else if(dir<0){
        auto it=lower_bound(poly.begin()+1,poly.begin()+top,point);
        return ccw(it[0],point,it[-1]);
    }else{
        auto it=upper_bound(poly.rbegin(),poly.rend()-top-1,point);
        return ccw(it==poly.rbegin()?poly[0]:it[-1],point,it[0]);
    }
}

typedef long long ll;

int n,m;
Poly<ll> pla,plb,cha,chb;
int topa,topb;
int ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    pla.resize(n);
    plb.resize(m);
    for(auto &p:pla)cin >> p;
    for(auto &p:plb)cin >> p;
    cha=convexHull(pla);
    chb=convexHull(plb);
    for(int i=0;i<cha.size();i++)if(cha[i]>cha[topa])topa=i;
    for(int i=0;i<chb.size();i++)if(chb[i]>chb[topb])topb=i;
    for(auto p:pla)ans+=isInside(p,chb,topb)<=0;
    for(auto p:plb)ans+=isInside(p,cha,topa)<=0;
    cout << ans;
}