#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int inf=2e9;

typedef long long ll;
typedef long double ld;

struct point{
    ll x,y;
    point():x(0),y(0){}
    point(ll x,ll y):x(x),y(y){}
};

ll cross(point x,point y,point z){
    return (y.x-x.x)*(z.y-y.y)-(z.x-y.x)*(y.y-x.y);
}

int n;
ll a[N],b[N];
ld ans[N],pre[N],suf[N];
deque<point> hull;

ld calc(point x,point y){
    return ld(n-1-2*x.x)*(x.y-y.y)/(x.x-y.x)+2*x.y;
}

ld solve(ll x,ll y){
    point p(x,y);
    int l=0,r=hull.size()-1;
    while(l<r){
        int m=(l+r)/2;
        if(cross(p,hull[m],hull[m+1])<=0)r=m;
        else l=m+1;
    }
    return calc(p,hull[l]);
}

ld solve2(ll x,ll y){
    point p(x,y);
    int l=0,r=hull.size()-1;
    while(l<r){
        int m=(l+r+1)/2;
        if(cross(p,hull[m],hull[m-1])>=0)l=m;
        else r=m-1;
    }
    return calc(p,hull[l]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++)cin >> a[i];
    for(int i=0;i<n;i++)cin >> b[i];
    for(int i=n/2;i<n;i++){
        point p(i,a[i]);
        while(hull.size()>1&&cross(hull.end()[-2],hull.back(),p)>=0)hull.pop_back();
        hull.emplace_back(p);
    }
    for(int i=0;i<n/2;i++){
        suf[i]=solve(i,a[i]);
        pre[i]=solve(i,b[i]);
    }
    for(int i=1;i<n/2;i++)pre[i]=max(pre[i],pre[i-1]);
    for(int i=n/2-2;i>=0;i--)suf[i]=max(suf[i],suf[i+1]);
    for(int i=0;i<n/2;i++)ans[i]=max(pre[i],suf[i+1]);
    hull.clear();
    for(int i=0;i<n/2;i++){
        point p(i,b[i]);
        while(hull.size()>1&&cross(hull.end()[-2],hull.back(),p)>=0)hull.pop_back();
        hull.emplace_back(p);
    }
    for(int i=n/2;i<n;i++){
        suf[i]=solve2(i,a[i]);
        pre[i]=solve2(i,b[i]);
    }
    for(int i=n/2+1;i<n;i++)pre[i]=max(pre[i],pre[i-1]);
    for(int i=n-2;i>=n/2;i--)suf[i]=max(suf[i],suf[i+1]);
    for(int i=n/2;i<n;i++)ans[i]=max(pre[i],suf[i+1]);
    cout << fixed << setprecision(12);
    for(int i=0;i<n;i++)cout << ans[i] << " ";
}