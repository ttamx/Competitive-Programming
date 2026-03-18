#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

const double EPS=1e-9;
const double SQ=sqrt(2);

struct Num{
    i128 w,s;
    Num():w(0),s(0){}
    Num(i128 v):w(v),s(0){}
    Num(i128 _w,i128 _s):w(_w),s(_s){}
    Num operator-(){
        return Num(-w,-s);
    }
    friend Num operator+(const Num &x,const Num &y){
        return Num(x.w+y.w,x.s+y.s);
    }
    friend Num operator-(const Num &x,const Num &y){
        return Num(x.w-y.w,x.s-y.s);
    }
    friend Num operator*(const Num &x,const Num &y){
        assert((x.s*y.s)%2==0);
        return Num(x.w*y.w+x.s*y.s/2,x.w*y.s+x.s*y.w);
    }
    Num &operator+=(const Num &o){
        return *this=*this+o;
    }
    Num &operator-=(const Num &o){
        return *this=*this-o;
    }
    Num &operator*=(const Num &o){
        return *this=*this*o;
    }
    bool operator<(const Num &o)const{
        return w<o.w||(w==o.w&&s<o.s);
    }
    bool operator==(const Num &o)const{
        return w==o.w&&s==o.s;
    }
    double eval(){
        return w+double(s)/SQ;
    }
};

struct point:complex<Num>{
    point(const complex<Num> &v):complex<Num>(v){}
    point(Num x,Num y):complex<Num>(x,y){}
    bool operator<(const point &o)const{
        Num rx=real(),ry=o.real();
        return rx<ry||(rx==ry&&imag()<o.imag());
    }
};

point rotate(int d){
    d%=8;
    if(d==0)return point(Num(1),Num(0));
    if(d==1)return point(Num(0,1),Num(0,1));
    if(d==2)return point(Num(0),Num(1));
    if(d==3)return point(Num(0,-1),Num(0,1));
    if(d==4)return point(Num(-1),Num(0));
    if(d==5)return point(Num(0,-1),Num(0,-1));
    if(d==6)return point(Num(0),Num(-1));
    if(d==7)return point(Num(0,1),Num(0,-1));
    assert(false);
    return point(Num(0));
}

int n;
int ang=0;
point cur(0,0);

set<point> p;
set<pair<point,point>> s;

pair<point,point> upair(const point &a,const point &b){
    return a<b?make_pair(a,b):make_pair(b,a);
}

Num dot(const point &a,const point &b){
    return (conj(a)*b).real();
}

Num cross(const point &a,const point &b){
    return (conj(a)*b).imag();
}

set<pair<point,point>> norm(const set<pair<point,point>> &s){
    set<pair<point,point>> res;
    map<point,set<point>> adj;
    for(auto [u,v]:s){
        adj[u].emplace(v);
        adj[v].emplace(u);
    }
    for(auto &[u,s]:adj){
        if(s.size()==2){
            point v=*s.begin();
            point w=*s.rbegin();
            if(cross(w-u,v-u)==Num(0,0)){
                adj[v].erase(u);
                adj[v].emplace(w);
                adj[w].erase(u);
                adj[w].emplace(v);
                s.clear();
            }
        }
    }
    for(auto &[u,s]:adj){
        for(auto v:s){
            res.emplace(upair(u,v));
        }
    }
    return res;
}

set<pair<point,point>> norm2(const set<pair<point,point>> &s){
    point mn=s.begin()->first;
    for(auto [u,v]:s){
        mn=min(mn,u);
        mn=min(mn,v);
    }
    set<pair<point,point>> res;
    for(auto [u,v]:s){
        res.emplace(upair(u-mn,v-mn));
    }
    return res;
}

bool eq(const point &u,const point &v){
    return u.real()==v.real()&&u.imag()==v.imag();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        string op;
        ll d;
        cin >> op >> d;
        if(op=="rotate"){
            ang+=d/45;
            ang%=8;
        }else if(op=="draw"){
            d*=2;
            point tar=cur+rotate(ang)*Num(d);
            p.emplace(cur);
            p.emplace(tar);
            s.emplace(upair(cur,tar));
            cur=tar;
        }else{
            d*=2;
            cur=cur+rotate(ang)*Num(d);
        }
    }
    s=norm2(norm(s));
    int ans=8;
    for(int d=1;d<=7;d++){
        point z=rotate(d);
        set<pair<point,point>> t;
        for(auto [u,v]:s){
            t.emplace(upair(u*z,v*z));
        }
        if(s==norm2(norm(t))){
            ans=min(ans,d);
            ans=min(ans,8-d);
        }
    }
    cout << ans*45;
}