#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct point{
    ll x,y;
    point(ll x,ll y):x(x),y(y){}
    constexpr ll abs2()const{
        return x*x+y*y;
    }
    constexpr ll dist2(const point &o)const{
        ll a=x-o.x;
        ll b=y-o.y;
        return a*a+b*b;
    }
    constexpr ld dist(const point &o)const{
        return sqrtl(this->dist2(o));
    }
    constexpr int cmp(const point &o)const{
        ll a=o.x*y;
        ll b=x*o.y;
        if(a<b)return -1;
        if(b>a)return 1;
        return 0;
    }
    constexpr bool operator<(const point &o)const{
        int res=this->cmp(o);
        if(res)return res==-1;
        return this->abs2()<o.abs2();
    }
};

ll cross(point p1,point p2,point p3){
    ll x1=p2.x-p1.x;
}

int n;

struct convexhull:set<point>{
    ld len=0;
    iterator cnext(iterator x){
        x=next(x);
        if(x==end())x=begin();
        return x;
    }
    iterator cprev(iterator x){
        if(x==begin())x=end();
        x=prev(x);
        return x;
    }
    void add(point p){
        auto [it,add]=insert(p);
        if(size()==1||!add)return;
        if(size()==2)len+=2*(begin()->dist(*cnext(begin())));
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;

}