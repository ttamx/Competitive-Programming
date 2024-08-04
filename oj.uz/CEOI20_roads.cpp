#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point{
    ll x,y;
    Point(ll _x,ll _y):x(_x),y(_y){}
    friend Point operator+(const Point &lhs,const Point &rhs){
        return Point(lhs.x+rhs.x,lhs.y+rhs.y);
    }
    friend bool operator<(const Point &lhs,const Point &rhs){
        return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
    }
};

ll cross(const Point &a,const Point &b){
    return a.x*b.y-a.y*b.x;
}

int ccw(const Point &a,const Point &b){

}

struct Segment{
    Point s,e;
    Segment(Point _s,Point _e):s(_s),e(_e){}
    bool operator<(const Segment &o)const{
        if(s.x>o.s.x){
            
        }
        return s.y<o.s.y;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
}