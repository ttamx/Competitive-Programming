#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=250005;

int n,q;
vector<tuple<int,int,int>> edges;
ll a[N];
int p[N];

int fp(int u){
    return p[u]=u==p[u]?u:fp(p[u]);
}

struct Point{
    ll x,y;
    Point(){}
    Point(ll x,ll y):x(x),y(y){}
    Point& operator+=(const Point &o){
        this->x+=o.x;
        this->y+=o.y;
        return *this;
    }
    Point& operator-=(const Point &o){
        this->x-=o.x;
        this->y-=o.y;
        return *this;
    }
    Point operator+(const Point &o)const{return Point(*this)+=o;}
    Point operator-(const Point &o)const{return Point(*this)-=o;}
};

constexpr ll cross(const Point &a,const Point &b){
    return a.x*b.y-b.x*a.y;
}

ll cross(Point a,Point b,Point o){
    return cross(a-o,b-o);
}

struct Cmp{
    bool operator()(const Point &a,const Point &b)const{
        return cross(a,b)<0;
    }
};

struct DS{
    Point st;
    multiset<Point,Cmp> dif;
    DS(){}
    void init(Point p){
        st=Point(0,0);
        dif.clear();
        dif.emplace(p);
    }
    void insert_front(Point p){
        Point d=st-p;
        for(auto it=dif.begin();it!=dif.end();it=dif.erase(it)){
            Point q=*it;
            if(cross(d,q)<0){
                break;
            }
            d+=q;
        }
        dif.emplace(d);
        st=p;
    }
    void insert(Point p){
        if(p.y<=dif.begin()->y)return;
        if(dif.size()==1){
            dif.clear();
            dif.emplace(p);
            return;
        }
        Point q=*dif.begin();
        dif.erase(dif.begin());
        q+=*dif.begin();
        dif.erase(dif.begin());
        st=q;
        insert_front(p);
        insert_front(Point(0,0));
    }
    void merge(DS &o){
        for(auto e:o.dif){
            dif.emplace(e);
        }
        multiset<Point,Cmp>().swap(o.dif);
    }
}ds[N];

struct CHT{
    struct Line{
        ll m,c;
        ll eval(ll x){
            return m*x+c;
        }
    };
    vector<Line> hull;
    void init(){
        hull.clear();
    }
    bool bad(Line x,Line y,Line z){
        return (z.c-x.c)*(x.m-y.m)<=(y.c-x.c)*(x.m-z.m);
    }
    void insert(ll m,ll c){
        Line v{m,c};
        while(hull.size()>=2&&bad(hull.end()[-2],hull.back(),v)){
            hull.pop_back();
        }
        hull.emplace_back(v);
    }
    ll query(ll x){
        int l=0,r=hull.size()-1;
        while(l<r){
            int m=(l+r)/2;
            if(hull[m+1].eval(x)>hull[m].eval(x))l=m+1;
            else r=m;
        }
        return hull[l].eval(x);
    }
}cht;

void runcase(){
    cin >> n;
    for(int i=1;i<=n;i++){
        a[i]=0;
    }
    edges.resize(n-1);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        a[u]+=w;
        a[v]+=w;
    }
    sort(edges.rbegin(),edges.rend());
    for(int i=1;i<=n;i++){
        p[i]=i;
        ds[i].init(Point(1,-a[i]));
    }
    for(auto [w,u,v]:edges){
        u=fp(u),v=fp(v);
        if(ds[u].dif.size()<ds[v].dif.size()){
            swap(u,v);
        }
        a[u]+=a[v]-2*w;
        ds[u].merge(ds[v]);
        ds[u].insert(Point(1,-a[u]));
        Point cur(0,0);
        p[v]=u;
    }
    cht.init();
    int root=fp(1);
    cht.insert(0,0);
    Point cur(0,0);
    cht.insert(cur.x,cur.y);
    for(auto d:ds[root].dif){
        cur+=d;
        cht.insert(cur.x,cur.y);
    }
    cin >> q;
    while(q--){
        ll t;
        cin >> t;
        cout << cht.query(t) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}