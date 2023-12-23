#include<bits/stdc++.h>

using namespace std;

template<class T>
struct point_t{
    T x,y;

    point_t():x(0),y(0){}
    point_t(const T &x,const T &y):x(x),y(y){}

    static constexpr T eps=static_cast<T>(1e-9);

    point_t& operator+=(const point_t &rhs){x+=rhs.x; y+=rhs.y; return *this;}
    point_t& operator-=(const point_t &rhs){x-=rhs.x; y-=rhs.y; return *this;}
    point_t& operator*=(const T &rhs){x*=rhs,y*=rhs; return *this;}
    point_t& operator/=(const T &rhs){x/=rhs,y/=rhs; return *this;}

    point_t operator-(){return point_t(-x,-y);}
    friend point_t operator+(const point_t &lhs,const point_t &rhs){return point_t(lhs)+=rhs;}
    friend point_t operator-(const point_t &lhs,const point_t &rhs){return point_t(lhs)-=rhs;}
    friend point_t operator*(const point_t &lhs,const T &rhs){return point_t(lhs)*=rhs;}
    friend point_t operator*(const T &lhs,const point_t &rhs){return point_t(rhs)*=lhs;}
    friend point_t operator/(const point_t &lhs,const T &rhs){return rhs*lhs;}

    friend T operator*(const point_t &lhs,const point_t &rhs){return lhs.x*rhs.x+lhs.y*rhs.y;} // dot product
    friend T operator^(const point_t &lhs,const point_t &rhs){return lhs.x*rhs.y-lhs.y*rhs.x;} // cross product

    friend T ccw(const point_t &lhs,const point_t &rhs){T x=lhs^rhs; return (x>eps)-(x<-eps);}
    friend T ccw(const point_t &lhs,const point_t &rhs,const point_t &o){return ccw(lhs-o,rhs-o);}

    friend bool operator==(const point_t &lhs,const point_t &rhs){return abs(lhs.x-rhs.x)<=eps&&abs(lhs.y-rhs.y)<=eps;}
    friend bool operator!=(const point_t &lhs,const point_t &rhs){return !(lhs==rhs);}
    friend bool operator<(const point_t &lhs,const point_t &rhs){return lhs.y+eps<rhs.y||(abs(lhs.y-rhs.y)<=eps&&lhs.x+eps<rhs.x);}
    friend bool operator>(const point_t &lhs,const point_t &rhs){return rhs<lhs;}
    friend bool operator<=(const point_t &lhs,const point_t &rhs){return !(lhs>rhs);}
    friend bool operator>=(const point_t &lhs,const point_t &rhs){return !(lhs<rhs);}

    friend T abs2(const point_t &p){return p.x*p.x+p.y*p.y;}
    friend T abs(const point_t &p){return sqrt(abs2(p));}
    friend T abs2(const point_t &lhs,const point_t &rhs){return abs2(rhs-lhs);}
    friend T abs(const point_t &lhs,const point_t &rhs){return abs(rhs-lhs);}

    friend istream& operator>>(istream &is,point_t &p){return is >> p.x >> p.y;}
    friend ostream& operator<<(ostream &os,const point_t &p){return os << p.x << ' ' << p.y;}
};

template<class T>
using polygon_t=vector<point_t<T>>;

template<class T>
polygon_t<T> convexHull(polygon_t<T> points){
    sort(points.begin(),points.end());
    polygon_t<T> hull;
    for(int t=0;t<2;t++){
        int sz=hull.size();
        for(auto p:points){
            while(hull.size()>=sz+2&&ccw(hull.back(),p,hull.end()[-2])<=0)hull.pop_back();
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(points.begin(),points.end());
    }
    if(hull.size()==2&&hull[0]==hull[1])hull.pop_back();
    return hull;
}

template<class T>
int isInside(const point_t<T> &point,const polygon_t<T> &poly,int top){
    if(point<poly[0]||point>poly[top])return -1;
    int dir=ccw(poly[top],point,poly[0]);
    if(dir==0){
        if(point==poly[0]||point==poly[top])return 0;
        return top==1||top==poly.size()-1?0:1;
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
polygon_t<ll> pla,plb,cha,chb;
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
    for(auto p:pla)ans+=isInside(p,chb,topb)>=0;
    for(auto p:plb)ans+=isInside(p,cha,topa)>=0;
    cout << ans;
}