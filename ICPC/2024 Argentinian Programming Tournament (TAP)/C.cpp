#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

struct Frac{
    i128 num,den;
    Frac(){}
    Frac(i128 x):num(x),den(1){}
    Frac(i128 x,i128 y):num(x),den(y){norm();}
    void norm(){
        if(den<0){
            num=-num;
            den=-den;
        }
    }
    friend Frac operator-(const Frac &o){return Frac(-o.num,o.den);}
    Frac& operator+=(const Frac &o){
        num=num*o.den+o.num*den;
        den*=o.den;
        norm();
        return *this;
    }
    Frac& operator-=(const Frac &o){
        num=num*o.den-o.num*den;
        den*=o.den;
        norm();
        return *this;
    }
    Frac& operator*=(const Frac &o){
        num*=o.num;
        den*=o.den;
        norm();
        return *this;
    }
    Frac& operator/=(const Frac &o){
        num*=o.den;
        den*=o.num;
        norm();
        return *this;
    }
    friend Frac operator+(const Frac &lhs,const Frac &rhs){return Frac(lhs)+=rhs;}
    friend Frac operator-(const Frac &lhs,const Frac &rhs){return Frac(lhs)-=rhs;}
    friend Frac operator*(const Frac &lhs,const Frac &rhs){return Frac(lhs)*=rhs;}
    friend Frac operator/(const Frac &lhs,const Frac &rhs){return Frac(lhs)/=rhs;}
    bool operator<(const Frac &o)const{return num*o.den<o.num*den;}
    bool operator>(const Frac &o)const{return num*o.den>o.num*den;}
    bool operator<=(const Frac &o)const{return num*o.den<=o.num*den;}
    bool operator>=(const Frac &o)const{return num*o.den>=o.num*den;}
    bool operator==(const Frac &o)const{return num*o.den==o.num*den;}
    bool operator!=(const Frac &o)const{return num*o.den!=o.num*den;}
    friend istream& operator>>(istream &is,Frac &o){
        ll x;
        is >> x;
        o=Frac(x);
        return is;
    }
};

int sgn(const Frac &x){
    if(x.num<0)return -1;
    if(x.num>0)return 1;
    return 0;
}

struct Point{
    Frac x,y;
    Point(){}
    Point(Frac _x,Frac _y):x(_x),y(_y){}
    friend Point operator-(const Point &p){return Point(-p.x,-p.y);}
    Point& operator+=(const Point &o){
        x+=o.x,y+=o.y;
        return *this;
    }
    Point& operator-=(const Point &o){
        x-=o.x,y-=o.y;
        return *this;
    }
    Point& operator*=(const Frac &k){
        x*=k,y*=k;
        return *this;
    }
    friend Point operator+(const Point &lhs,const Point &rhs){return Point(lhs)+=rhs;}
    friend Point operator-(const Point &lhs,const Point &rhs){return Point(lhs)-=rhs;}
    friend Point operator*(const Point &p,const Frac &k){return Point(p)*=k;}
    friend Point operator*(const Frac &k,const Point &p){return Point(p)*=k;}
};

Frac dot(const Point &p,const Point &q){
    return p.x*q.x+p.y*q.y;
}

Frac cross(const Point &p,const Point &q){
    return p.x*q.y-p.y*q.x;
}

bool on_segment(const Point &s,const Point &e,const Point &p){
    return sgn(cross(s-p,e-p))==0&&sgn(dot(s-p,e-p))<=0;
}

bool on_segment2(const Point &s,const Point &e,const Point &p){
    return sgn(cross(s-p,e-p))==0&&sgn(dot(s-p,e-p))<0;
}

bool is_intersect(Point a,Point b,Point c,Point d){
    int oa=sgn(cross(d-c,a-c));
    int ob=sgn(cross(d-c,b-c));
    int oc=sgn(cross(b-a,c-a));
    int od=sgn(cross(b-a,d-a));
    return oa*ob<0&&oc*od<0;
}

bool in_polygon(const vector<Point> &p,const Point &a){
    int cnt=0,n=p.size();
    for(int i=0;i<n;i++){
        Point q=p[(i+1)%n];
        if(on_segment(p[i],q,a))return true;
        cnt^=((a.y<p[i].y)-(a.y<q.y))*sgn(cross(p[i]-a,q-a))>0;
    }
    return cnt;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    Point sun,ape;
    ll sunz,apez;
    cin >> sun.x >> sun.y >> sunz;
    cin >> ape.x >> ape.y >> apez;
    vector<Point> a(n);
    for(auto &p:a){
        cin >> p.x >> p.y;
    }
    ape+=(ape-sun)*Frac(apez,sunz-apez);
    // if(!in_polygon(a,ape)){
    //     cout << "S";
    //     exit(0);
    // }
    for(int i=0;i<n;i++){
        Point p=a[i];
        Point q=(a[i]+a[(i+1)%n])*Frac(1,2);
        for(int j=0;j<n;j++){
            if(is_intersect(p,ape,a[j],a[(j+1)%n])){
                cout << "S";
                exit(0);
            }
            if(is_intersect(q,ape,a[j],a[(j+1)%n])){
                cout << "S";
                exit(0);
            }
        }
    }
    cout << "N";
}