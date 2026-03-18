#include<bits/stdc++.h>

using namespace std;

using ll = long long;

using P = pair<ll,ll>;

ll cross(P a,P b){
    return a.first*b.second-a.second*b.first;
}

ll cross(P a,P b,P o){
    a.first-=o.first,a.second-=o.second;
    b.first-=o.first,b.second-=o.second;
    return cross(a,b);
}

struct LowerHull{
    multiset<P> hull;
    void insert(P p){
        if(inside(p))return;
        auto it=hull.lower_bound(p);
        if(it!=hull.end()){
            while(next(it)!=hull.end()&&cross(*it,*next(it),p)<=0){
                it=hull.erase(it);
            }
        }
        if(it!=hull.begin()){
            while(--it!=hull.begin()&&cross(*it,*prev(it),p)>=0){
                it=hull.erase(it);
            }
        }
        hull.emplace(p);
    }
    bool inside(P p){
        auto it=hull.lower_bound(p);
        if(it==hull.end())return false;
        if(it==hull.begin())return p==*it;
        return cross(*it,p,*prev(it))>=0;
    }
}h1,h2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    while(q--){
        int op,x,y;
        cin >> op >> x >> y;
        if(op==1){
            h1.insert(P(x,y));
            h2.insert(P(-x,-y));
        }else{
            cout << (h1.inside(P(x,y))&&h2.inside(P(-x,-y))?"YES":"NO") << "\n";
        }
    }
}