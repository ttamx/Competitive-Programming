#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point{
    ll x,y;
    Point(ll _x,ll _y):x(_x),y(_y){}
    friend Point operator-(const Point &l,const Point &r){
        return Point(l.x-r.x,l.y-r.y);
    }
    bool operator<(const Point &o){
        return x<o.x||(x==o.x&&y<o.y);
    }
};

ll cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

ll dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

struct DSU{
    int n;
    vector<int> p;
    DSU(int _n):n(n),p(n){
        iota(p.begin(),p.end(),0);
    }
    int find(int u){
        return u==p[u]?u:p[u]=find(p[u]);
    }
    bool merge(int u,int v){
        u=find(u),v=find(v);
        if(u==v)return false;
        return p[u]=v,true;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m;
    cin >> m;
    vector<pair<Point,Point>> fences(m);
    map<Point,int> id;
    for(auto &[a,b]:fences){
        cin >> a.x >> a.y >> b.x >> b.y;
        id[a],id[b];
    }
    int n=0;
    vector<Point> points;
    for(auto &[x,y]:id){
        y=n++;
        points.emplace_back(x);
    }
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u=id[fences[i].first];
        int v=id[fences[i].second];
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    for(int i=0;i<n;i++){
        if(adj[i].size()%2==1){
            cout << "yes";
            exit(0);
        }
        // sort(adj[i].begin(),adj[i].end(),[&](pair<int,int> a,pair<int,int> b){
        //     int x=a.first,y=b.second;
        //     if(cross(points[y]-points[i],points[x]-points[i])<=1)return true;
        // });
    }
    cout << "no\n";
}