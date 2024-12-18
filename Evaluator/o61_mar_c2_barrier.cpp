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
struct halfhull_t{
    set<point_t<T>> hull;
    T perimeter;

    halfhull_t():hull(),perimeter(0){}

    int isInside(const point_t<T> &point){
        auto it=hull.lower_bound(point);
        if(it==hull.end())return -1;
        if(it==hull.begin())return point==*it?0:-1;
        return ccw(*it,point,*prev(it));
    }

    void insert(const point_t<T> &point){
        if(isInside(point)>=0)return;
        auto it=hull.lower_bound(point);
        if(it!=hull.end()&&it!=hull.begin()){
            perimeter-=abs(*it,*prev(it));
        }
        if(it!=hull.end()){
            while(next(it)!=hull.end()&&ccw(*it,*next(it),point)<=0){
                perimeter-=abs(*it,*next(it));
                it=hull.erase(it);
            }
            perimeter+=abs(point,*it);
        }
        if(it!=hull.begin()){
            while((--it)!=hull.begin()&&ccw(*it,point,*prev(it))<=0){
                perimeter-=abs(*it,*prev(it));
                it=hull.erase(it);
            }
            perimeter+=abs(point,*it);
        }
        hull.emplace(point);
    }
};

template<class T>
struct dynamichull_t{
    halfhull_t<T> righthull,lefthull;
    T perimeter;

    dynamichull_t():righthull(),lefthull(),perimeter(0){}

    void insert(const point_t<T> &point){
        righthull.insert(point);
        lefthull.insert(point*(-1));
        perimeter=lefthull.perimeter+righthull.perimeter;
    }
};

int n;
dynamichull_t<long double> ch;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    while(n--){
        point_t<long double> p;
        cin >> p;
        ch.insert(p);
        cout << fixed << setprecision(6) << ch.perimeter << "\n";
    }
}