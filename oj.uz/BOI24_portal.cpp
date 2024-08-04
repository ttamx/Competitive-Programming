#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n;

struct Point{
    ll x,y;
    Point operator+(const Point &p)const{return {x+p.x,y+p.y};}
    Point operator-(const Point &p)const{return {x-p.x,y-p.y};}
    Point operator*(ll k)const{return {x*k,y*k};}
}p[N];

ll cross(Point a,Point b){return a.x*b.y-b.x*a.y;}

Point gcd(Point a,Point b){
    ll d=a.x?a.x/gcd(a.x,b.x):a.y/gcd(a.y,b.y);
    return {a.x/d,a.y/d};
}

pair<Point,Point> gcd2(Point u,Point v,Point q){
    if(cross(u,v)==0)return {gcd(u,v),q};
    if(cross(u,q)==0)return {gcd(u,q),v};
    if(cross(v,q)==0)return {u,gcd(v,q)};
    ll d=cross(u,v);
    ll a=cross(q,v)/d;
    ll b=cross(u,q)/d;
    return gcd2(u,q-u*a-v*b,v);

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> p[i].x >> p[i].y;
    for(int i=2;i<=n;i++)p[i]=p[i]-p[1];
    bool ok=false;
    for(int i=3;i<=n;i++)if(cross(p[2],p[i])!=0)ok=true;
    if(!ok)cout << -1,exit(0);
    Point u=p[2],v=p[3];
    for(int i=4;i<=n;i++)tie(u,v)=gcd2(u,v,p[i]);
    cout << abs(cross(u,v));
}