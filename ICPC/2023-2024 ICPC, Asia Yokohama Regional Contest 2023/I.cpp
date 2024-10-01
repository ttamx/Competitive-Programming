#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point{
    ll x,y;
    Point(){}
    Point(ll x,ll y):x(x),y(y){}
    friend Point operator-(const Point &l,const Point &r){return Point(l.x-r.x,l.y-r.y);}
};

ll cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

ll cross(Point a,Point b,Point o){
    return cross(a-o,b-o);
}

int n,m;
vector<Point> pts,req;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    pts.resize(n+1);
    pts[0]=Point(0,0);
    for(int i=1;i<=n;i++){
        cin >> pts[i].x;
    }
    for(int i=1;i<=n;i++){
        cin >> pts[i].y;
    }
    sort(pts.begin()+1,pts.end(),[&](Point p,Point q){
        return p.x*q.y>p.y*q.x;
    });
    for(int i=1;i<=n;i++){
        pts[i].x+=pts[i-1].x;
        pts[i].y+=pts[i-1].y;
    }
    req.resize(m);
    for(auto &p:req){
        cin >> p.x;
    }
    for(auto &p:req){
        cin >> p.y;
    }
    sort(req.begin(),req.end(),[&](Point p,Point q){
        return p.x*q.y>p.y*q.x;
    });
    for(int i=1;i<m;i++){
        req[i].x+=req[i-1].x;
        req[i].y+=req[i-1].y;
    }
    for(auto p:req){
        for(int i=1;i<=n;i++){
            if(cross(pts[i],p,pts[i-1])<0){
                cout << "No";
                exit(0);
            }
        }
    }
    cout << "Yes";
}