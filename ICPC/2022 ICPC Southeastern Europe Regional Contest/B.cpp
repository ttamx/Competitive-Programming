#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MUL=1e6;

struct Point{
    ll x,y;
    Point():x(0),y(0){}
    Point(ll _x,ll _y):x(_x),y(_y){}
    friend Point operator-(const Point &l,const Point &r){
        return Point(l.x-r.x,l.y-r.y);
    }
};

ll cross(const Point &a,const Point &b){
    return a.x*b.y-b.x*a.y;
}
ll cross(const Point &a,const Point &b,const Point &o){
    return cross(a-o,b-o);
}

ll dot(const Point &a,const Point &b){
    return a.x*b.x+a.y*b.y;
}
ll dot(const Point &a,const Point &b,const Point &o){
    return dot(a-o,b-o);
}

int solve(const vector<Point> &a,const Point &o){
    int res=0;
    deque<Point> dq;
    for(auto p:a){
        while(!dq.empty()&&cross(dq.front(),p,o)<=0){
            dq.pop_front();
        }
        dq.emplace_back(p);
        res=max(res,(int)dq.size());
    }
    return res;
}

int n,m;
vector<Point> a,b,hull;
int ans=0;

void work(const Point &u,const Point &v,const Point &w){
    vector<Point> c,d;
    vector<bool> used(n);
    for(int i=0;i<n;i++){
        ll cr=cross(w,a[i],u);
        if(cr>0||(cr==0&&dot(w,a[i],u)<0)){
            used[i]=true;
            c.emplace_back(a[i]);
        }
    }
    for(int i=0;i<n;i++){
        if(used[i])continue;
        ll cr=cross(v,a[i],u);
        if(cr<0||(cr==0&&dot(v,a[i],u)<0)){
            used[i]=true;
            d.emplace_back(a[i]);
        }
    }
    auto cmp=[&](const Point &a,const Point &b){
        return cross(a,b,u)>0;
    };
    sort(c.begin(),c.end(),cmp);
    sort(d.begin(),d.end(),cmp);
    c.insert(c.end(),d.begin(),d.end());
    // cerr << "ORIGIN AT(" << u.x << "," << u.y << ")\n";
    // cerr << "CANDIDATES : ";
    // for(auto p:c){
    //     cerr << "(" << p.x << "," << p.y << ") ";
    // }
    // cerr << "\n";
    // cerr << "MAX SET = " << solve(c,u) << "\n";
    ans=max(ans,solve(c,u));
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    a.resize(n);
    b.resize(m);
    for(int i=0;i<n;i++){
        double x,y;
        cin >> x >> y;
        a[i].x=x*MUL+.5;
        a[i].y=y*MUL+.5;
    }
    for(int i=0;i<m;i++){
        double x,y;
        cin >> x >> y;
        b[i].x=x*MUL+.5;
        b[i].y=y*MUL+.5;
    }
    if(m==1){
        work(b[0],Point(b[0].x,0),Point(b[0].x,0));
        work(b[0],Point(b[0].x,MUL),Point(b[0].x,MUL));
        cout << ans << "\n";
        exit(0);
    }
    sort(b.begin(),b.end(),[&](const Point &a,const Point &b){
        return a.x<b.x||(a.x==b.x&&a.y<b.y);
    });
    for(int t=0;t<2;t++){
        int sz=hull.size();
        for(auto p:b){
            while(hull.size()>=sz+2&&cross(hull.back(),p,hull.end()[-2])<=0){
                hull.pop_back();
            }
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(b.begin(),b.end());
    }
    // for(auto p:hull){
    //     cerr << "(" << p.x << "," << p.y << ") ";
    // }
    int hs=hull.size();
    for(int i=0;i<hs;i++){
        Point u=hull[i],v=hull[(i+1)%hs],w=hull[(i+hs-1)%hs];
        work(u,v,w);
    }
    cout << ans << "\n";
}

/*

6 1
0.2 0.6
0.8 0.6
0.6 0.2
0.1 0.2
0.6 0.8
0.6 0.6
0.5 0.5

0 7
0.2 0.6
0.8 0.6
0.6 0.2
0.1 0.2
0.6 0.8
0.6 0.6
0.5 0.5

COLINEAR
2 2
0.1 0.1
0.9 0.9
0.4 0.4
0.6 0.6


SINGLE STRAW
2 1
0.1 0.1
0.9 0.9
0.4 0.4

SPADE
4 3
0.5 0.1
0.2 0.7
0.9 0.7
0.5 0.5

0.3 0.3
0.7 0.3
0.5 0.9
*/