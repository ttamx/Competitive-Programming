#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

struct Point{
    ll x,y;
    Point(){}
    Point(ll _x,ll _y):x(_x),y(_y){}
    friend Point operator-(const Point &lhs,const Point &rhs){
        return Point(lhs.x-rhs.x,lhs.y-rhs.y);
    }
};

ll cross(Point a,Point b){
    return a.x*b.y-b.x*a.y;
}

ll cross(Point a,Point b,Point o){
    return cross(a-o,b-o);
}

i128 sq(i128 x){
    return x*x;
}

ll area(Point a,Point b,Point c){
    return abs(cross(a,b,c));
}

void runcase(){
    int n;
    cin >> n;
    Point c;
    ll r;
    cin >> c.x >> c.y >> r;
    vector<Point> a(n);
    for(auto &p:a){
        cin >> p.x >> p.y;
    }
    ll cur=0,ans=0;
    auto check=[&](int i,int j){
        if(cross(a[j],c,a[i])<0)return false;
        i128 x1=a[i].x,y1=a[i].y;
        i128 x2=a[j].x,y2=a[j].y;
        i128 num=sq((y1-y2)*c.x-(x1-x2)*c.y+x1*y2-x2*y1);
        i128 den=sq(y1-y2)+sq(x1-x2);
        return num>=den*r*r;
    };
    for(int i=0,j=0;i<n;i++){
        if(i>0){
            if(j==i-1){
                cur+=area(a[i-1],a[j],a[(j+1)%n]);
                j=(j+1)%n;
            }
            cur-=area(a[i-1],a[i],a[j]);
        }
        while(check(i,(j+1)%n)){
            cur+=area(a[i],a[j],a[(j+1)%n]);
            j=(j+1)%n;
        }
        if(check(i,j)){
            ans=max(ans,cur);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}