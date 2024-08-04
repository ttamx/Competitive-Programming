#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;

const db EPS=1e-9;

struct Point{
    db x,y;
    Point():x(0),y(0){}
    Point(db _x,db _y):x(_x),y(_y){}
    bool operator<(const Point &o)const{
        return y<o.y-EPS||(abs(y-o.y)<=EPS&&x<o.x-EPS);
    }
    friend Point operator-(const Point &p){return Point(-p.x,-p.y);}
    friend Point operator+(const Point &lhs,const Point &rhs){return Point(lhs.x+rhs.x,lhs.y+rhs.y);}
    friend Point operator-(const Point &lhs,const Point &rhs){return Point(lhs.x-rhs.x,lhs.y-rhs.y);}
    friend Point operator*(const Point &p,const db &k){return Point(p.x*k,p.y*k);}
    friend Point operator/(const Point &p,const db &k){return Point(p.x/k,p.y/k);}
    friend ostream& operator<<(ostream &os,const Point &o){
        return os << "(" << o.x << "," << o.y << ")";
    }
};

db cross(const Point &a,const Point &b){
    return a.x*b.y-a.y*b.x;
}

db dot(const Point &a,const Point &b){
    return a.x*b.x+a.y*b.y;
}

int sgn(db x){
    if(x>EPS)return 1;
    if(x<-EPS)return -1;
    return 0;
}

int ccw(const Point &a,const Point &b){
    return sgn(cross(a,b));
}

int ccw(const Point &a,const Point &b,const Point &o){
    return ccw(a-o,b-o);
}

vector<Point> convex_hull(vector<Point> pts){
    sort(pts.begin(),pts.end());
    vector<Point> res;
    for(int t=0;t<2;t++){
        int sz=res.size();
        for(auto p:pts){
            while(res.size()>=2+sz&&ccw(p,res.back(),res.end()[-2])<=0){
                res.pop_back();
            }
            res.emplace_back(p);
        }
        res.pop_back();
        reverse(pts.begin(),pts.end());
    }
    return res;
}

bool on_segment(Point s,Point e,Point p){
    return ccw(s,e,p)==0&&sgn(dot(s-p,e-p))<=0;
}

vector<Point> segment_intersection(Point a,Point b,Point c,Point d){
    db oa=cross(a-d,c-d),ob=cross(b-d,c-d);
    db oc=cross(c-b,a-b),od=cross(d-b,a-b);
    if(sgn(oa)*sgn(ob)<0&&sgn(oc)*sgn(od)<0){
        return {(a*ob-b*oa)/(ob-oa)};
    }
    set<Point> res;
    if(on_segment(c,d,a))res.emplace(a);
    if(on_segment(c,d,b))res.emplace(b);
    if(on_segment(a,b,c))res.emplace(c);
    if(on_segment(a,b,d))res.emplace(d);
    return {res.begin(),res.end()};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<vector<int>> dice(2);
    for(auto &die:dice){
        int s;
        cin >> s;
        die.resize(s);
        for(auto &x:die)cin >> x;
        sort(die.begin(),die.end());
    }
    int n=dice[0].size();
    int m=dice[1].size();
    auto calc=[&](int i,int x){
        auto &die=dice[i];
        int l=lower_bound(die.begin(),die.end(),x)-die.begin();
        int r=upper_bound(die.begin(),die.end(),x)-die.begin();
        return l+r;
    };
    ll tot=0;
    for(auto x:dice[0])tot+=calc(1,x);
    if(tot<1LL*n*m){
        swap(dice[0],dice[1]);
        swap(n,m);
    }
    vector<int> a;
    for(auto &die:dice){
        for(auto &x:die){
            a.emplace_back(x);
            a.emplace_back(x+1);
            if(x>1)a.emplace_back(x-1);
        }
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    vector<Point> pts;
    for(auto x:a)pts.emplace_back(Point(calc(0,x),calc(1,x)));
    pts=convex_hull(pts);
    db ansy=m*2,ansx=0;
    Point x1(n,-1e9),x2(n,1e9);
    Point y1(-1e9,m),y2(1e9,m);
    Point p=pts.back(),q;
    for(int i=0;i<pts.size();i++){
        q=pts[i];
        for(auto o:segment_intersection(p,q,x1,x2)){
            ansy=min(ansy,o.y);
        }
        for(auto o:segment_intersection(p,q,y1,y2)){
            ansx=max(ansx,o.x);
        }
        p=q;
    }
    ansy/=m*2;
    ansx/=n*2;
    cout << fixed << setprecision(10);
    cout << ansy << " " << ansx;
}