#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int N=3e5+5;

struct point{
    ll x,y;
    point():x(0),y(0){}
    point(ll x,ll y):x(x),y(y){}
    ll norm(){
        return x*x+y*y;
    }
    bool isupper(){
        return y>0||(y==0&&x>0);
    }
    int cmp(point o){// -1 => less, 0 => equal, 1 => greater (compare with angle in range 0-360)
        bool a=isupper();
        bool b=o.isupper();
        if(a!=b)return a?-1:1;
        ll res=x*o.y-o.x*y;
        if(res==0)return 0;
        return res<0?-1:1;
    }
};

int n;
vector<point> v;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    ld sx=0,sy=0;
    for(int i=0;i<n;i++){
        ll a,b,c,d;
        cin >> a >> b >> c >> d;
        ll x=a-b,y=c-d;
        if(x==0&&y==0)continue;
        point pt(x,y),pt2(-x,-y);
        if(!pt.isupper())sx+=x,sy+=y;
        v.emplace_back(pt);
        v.emplace_back(pt2);
    }
    sort(v.begin(),v.end(),[&](point x,point y){
        int res=x.cmp(y);
        //if(res==0)return x.norm()<y.norm();
        return res==-1;
    });
    ld ans=sx*sx+sy*sy;
    for(auto pt:v){
        sx+=pt.x,sy+=pt.y;
        ans=max(ans,sx*sx+sy*sy);
    }
    cout << setprecision(40) << ans;
}