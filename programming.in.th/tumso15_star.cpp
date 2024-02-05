#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;
const db EPS=1e-9;
const db PI=acos(db(-1));

const db c=(3.l-sqrt(5.l))/2.0;
const db ang=PI/23;
const db dx=cos(PI);
const db dy=sin(PI);

struct point{
    db x,y;
    point(db _x,db _y):x(_x),y(_y){}
    point(db a):x(cos(a)),y(sin(a)){}
};

db cross(point o,point a,point b){
    db x1=a.x-o.x,y1=a.y-o.y;
    db x2=b.x-o.x,y2=b.y-o.y;
    return x1*y2-x2*y1;
}

int ccw(point o,point a,point b){
    db res=cross(o,a,b);
    if(res<-EPS)return -1;
    if(res>EPS)return 1;
    return 0;
}

bool isect(point a,point b,point c,point d){
    int x=ccw(a,b,c)*ccw(a,b,d);
    int y=ccw(c,d,a)*ccw(c,d,b);
    return x<1&&y<1;
}

vector<pair<point,point>> star;

void runcase(){
    db r,x,y;
    cin >> r >> x >> y;
    if(abs(x)<EPS&&abs(y)<EPS)return void(cout << "STAR\n");
    db r2=r*c;
    point ray(x,y),ray2(x+100*r*dx,y+100*r*dy);
    bool ans=false;
    for(auto [a,b]:star){
        a.x*=r,a.y*=r;
        b.x*=r2,b.y*=r2;
        ans^=isect(ray,ray2,a,b);
    }
    cout << (ans?"STAR":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    db ang1=PI/2,ang2=3*PI/10,dif=2*PI/5;
    for(int i=0;i<5;i++){
        star.emplace_back(point(ang1),point(ang2));
        star.emplace_back(point(ang1),point(ang2+dif));
        ang1+=dif,ang2+=dif;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}