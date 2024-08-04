#include<bits/stdc++.h>

using namespace std;

using db = long double;

const db EPS=1e-9;

struct Point{
    db x,y;
    Point():x(0),y(0){}
    Point(db _x,db _y):x(_x),y(_y){}
    friend Point operator-(const Point &p){
        return Point(-p.x,-p.y);
    }
    friend Point operator+(const Point &lhs,const Point &rhs){
        return Point(lhs.x+rhs.x,lhs.y+rhs.y);
    }
    friend Point operator-(const Point &lhs,const Point &rhs){
        return Point(lhs.x-rhs.x,lhs.y-rhs.y);
    }
    friend Point operator*(const Point &p,const db &k){
        return Point(p.x*k,p.y*k);
    }
    friend Point operator/(const Point &p,const db &k){
        return Point(p.x/k,p.y/k);
    }
    friend ostream& operator<<(ostream &os,const Point &o){
        return os << "(" << o.x << "," << o.y << ")";
    }
};

db abs2(const Point &p){
    return p.x*p.x+p.y*p.y;
}

db abs(const Point &p){
    return sqrtl(abs2(p));
}

db cross(const Point &a,const Point &b){
    return a.x*b.y-a.y*b.x;
}

int ccw(const Point &a,const Point &b){
    db res=cross(a,b);
    if(res>EPS)return 1;
    if(res<-EPS)return -1;
    return 0;
}

int ccw(const Point &a,const Point &b,const Point &o){
    return ccw(a-o,b-o);
}

Point unit(const Point &p){
    db r=abs(p);
    return Point(p.x,p.y)/r;
}

Point midpoint(const Point &p1,const Point &p2){
    return (p1+p2)/2;
}

struct Pyramid{
    db h,l,l2;
    vector<pair<Point,Point>> base;
    void read(){
        db x1,y1,x2,y2,h;
        cin >> x1 >> y1 >> x2 >> y2 >> h;
        Point p1=Point(x1,y1);
        Point p2=Point(x2,y2);
        Point vec=p2-p1;
        l=sqrtl(h*h+abs2(p2-p1)/4);
        l2=sqrtl(l*l+abs2(p2-p1)/4);
        for(int i=0;i<4;i++){
            base.emplace_back(p1,p2);
            swap(vec.x,vec.y);
            vec.x=-vec.x;
            p1=p2;
            p2=p2+vec;
        }
    }
    Point corner(int i){
        return base[i].first;
    }
    Point project(int i){
        auto [p1,p2]=base[i];
        Point p=p2-p1;
        Point q=unit(Point(-p.y,p.x))*l;
        return midpoint(p1,p2)+q;
    }
    bool check(int i,Point p){
        Point o=project(i);
        auto [r,l]=base[i];
        p=p-o,l=l-o,r=r-o;
        if(ccw(l,r)==1)swap(l,r);
        return ccw(p,l)>=0&&ccw(r,p)>=0;
    }
    bool check_side(int i,Point p){
        auto [p1,p2]=base[i];
        return ccw(p,p2,p1)>=0;
    }
    bool check_side(int i,pair<Point,Point> p){
        auto [p1,p2]=p;
        return check_side(i,p1)||check_side(i,p2);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    Pyramid p1,p2;
    p1.read();
    p2.read();
    db ans=1e100;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            ans=min(ans,p1.l2+p2.l2+abs(p1.corner(i)-p2.corner(j)));
        }
    }
    for(int t=0;t<2;t++){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                Point p=p1.corner(i);
                if(p2.check(j,p)&&p2.check_side(j,p)){
                    ans=min(ans,p1.l2+abs(p-p2.project(j)));
                }
            }
        }
        swap(p1,p2);
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            Point p=p1.project(i);
            Point q=p2.project(j);
            if(p1.check(i,q)&&p1.check_side(i,p2.base[j])){
                if(p2.check(j,p)&&p2.check_side(j,p1.base[i])){
                    ans=min(ans,abs(p-q));
                }
            }
        }
    }
    cout << fixed << setprecision(10) << ans;
}