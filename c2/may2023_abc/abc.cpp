#include "abc.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const bool DBG=false;

struct point{
    ll x,y;
    int id;
    point(ll x=0,ll y=0,int id=0):x(x),y(y),id(id){}
};

ll cross(point p0,point p1,point p2){
    ll x1=p1.x-p0.x;
    ll y1=p1.y-p0.y;
    ll x2=p2.x-p1.x;
    ll y2=p2.y-p1.y;
    return x1*y2-x2*y1;
}

int n;
ll qa[N],qb[N],qc[N];
point p[N];

ll calc(int l,int r){
    if(l>r)swap(l,r);
    ll a=qa[r]-qa[l];
    ll b=qb[r]-qb[l];
    ll c=qc[r]-qc[l];
    return (a-b)*(a-b)+(b-c)*(b-c)+(c-a)*(c-a);
}

pair<int, int> max_unbalance(string S){
    n=S.size();
    for(int i=1;i<=n;i++){
        qa[i]=qa[i-1]+(S[i-1]=='a');
        qb[i]=qb[i-1]+(S[i-1]=='b');
        qc[i]=qc[i-1]+(S[i-1]=='c');
        p[i]={qa[i]-qb[i],qb[i]-qc[i],i};
        if(p[i].y<p[0].y||(p[i].y==p[0].y&&p[i].x<p[0].x))swap(p[0],p[i]);
    }
    sort(p+1,p+n+1,[&](point p1,point p2){
        ll x1=p1.x-p[0].x;
        ll y1=p1.y-p[0].y;
        ll x2=p2.x-p[0].x;
        ll y2=p2.y-p[0].y;
        if((x1^x2^y1^y2)<0)return (x2^y2)<0;
        if(y1*x2==y2*x1)return calc(p[0].id,p1.id)<calc(p[0].id,p2.id);
        return y1*x2<y2*x1;
    });
    if(DBG){
        cerr << "SORTED POINTS\n";
        for(int i=0;i<=n;i++)cerr << p[i].x << " " << p[i].y << " " << p[i].id << "\n";
        cerr << "\n";
    }
    deque<point> hull;
    hull.emplace_back(p[0]);
    for(int i=1;i<=n;i++){
        if(p[i].x==p[i-1].x&&p[i].y==p[i-1].y)continue;
        while(hull.size()>1&&cross(hull[1],hull[0],p[i])<0)hull.pop_front();
        hull.emplace_front(p[i]);
    }
    while(hull.size()>1&&cross(hull[1],hull[0],p[0])<0)hull.pop_front();
    if(DBG){
        cerr << "CONVEX HULL\n";
        for(auto x:hull)cerr << x.x << " " << x.y << " " << x.id << "\n";
        cerr << "\n";
    }
    ll mx=LLONG_MIN;
    int idx=0;
    for(int i=1;i<hull.size();i++){
        ll res=calc(hull[0].id,hull[i].id);
        if(res>mx){
            mx=res;
            idx=i;
        }
    }
    pair<int,int> ans(hull[0].id,hull[idx].id);
    for(int i=0;i<hull.size();i++){
        ll res=calc(hull[i].id,hull[idx].id);
        ll pre=res;
        if(res>mx){
            mx=res;
            ans={hull[i].id,hull[idx].id};
        }
        while(idx+1<hull.size()&&(res=calc(hull[i].id,hull[idx+1].id))>pre){
            idx++;
            if(res>mx){
                mx=res;
                ans={hull[i].id,hull[idx].id};
            }
            pre=res;
        }
    }
    if(ans.first>ans.second)swap(ans.first,ans.second);
    return ans;
}