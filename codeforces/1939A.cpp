#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point{
    ll x,y;
    Point():x(0),y(0){}
    Point(ll _x,ll _y):x(_x),y(_y){}
    friend Point operator-(const Point &lhs,const Point &rhs){
        return Point(lhs.x-rhs.x,lhs.y-rhs.y);
    }
};

int sgn(ll x){
    return x<0?-1:x>0?1:0;
}

ll cross(Point a,Point b){
    return a.x*b.y-b.x*a.y;
}

ll dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

ll norm(Point a){
    return a.x*a.x+a.y*a.y;
}

const int N=80005;

int task,group;
int n;
vector<Point> pt;

void task1(){
    vector<int> id(n);
    iota(id.begin(),id.end(),0);
    int st=0;
    for(int i=1;i<n;i++)if(pt[i].y<pt[st].y||(pt[i].y==pt[st].y&&pt[i].y<pt[st].y))st=i;
    swap(id[0],id[st]);
    sort(id.begin()+1,id.end(),[&](int i,int j){
        return norm(pt[i]-pt[st])>norm(pt[j]-pt[st]);
    });
    vector<int> ans{id[0],id[1]};
    for(int _i=2;_i<n;_i++){
        int i=id[_i];
        if(dot(pt[ans.end()[-2]]-pt[ans.back()],pt[i]-pt[ans.back()])>0){
            ans.emplace_back(i);
        }else{
            int j=ans.back();
            ans.pop_back();
            ans.emplace_back(i);
            ans.emplace_back(j);
        }
    }
    for(auto x:ans)cout << x+1 << " ";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> task >> group;
    cin >> n;
    pt.resize(n);
    for(auto &p:pt)cin >> p.x >> p.y;
    if(task==1)task1();
}