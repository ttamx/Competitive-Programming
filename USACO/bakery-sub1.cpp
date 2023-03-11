#include<bits/stdc++.h>

using namespace std;

const bool DBG=false;

typedef long long ll;
typedef double db;

struct line{
    db m,c;
    line():m(-1e18),c(-1e18){}
    line(db _m,db _c):m(_m),c(_c){}
    db get(db x){
        return m*x+c;
    }
    db insect(line o){
        if(m==o.m)return -1;
        return (o.c-c)/(m-o.m);
    }
    bool operator<(line o){
        if(m==o.m)return c<o.c;
        return m<o.m;
    }
};

void runcase(){
    int n;
    db tc,tm;
    cin >> n >> tc >> tm;
    vector<line> v;
    for(int i=0;i<n;i++){
        db a,b,c;
        cin >> a >> b >> c;
        v.emplace_back(-a/b,(a*tc+b*tm-c)/b);
    }
    ll ans=0;
    for(int i=0;i<n;i++)ans=max(ans,ll(v[i].get(0)));
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            db x=ceil(v[i].insect(v[j]));
            if(x>=0){
                db mx=0;
                for(int k=0;k<n;k++)mx=max(mx,v[k].get(x));
                ans=min(ans,ll(x+ceil(mx)));
            }
            x=floor(v[i].insect(v[j]));
            if(x>=0){
                db mx=0;
                for(int k=0;k<n;k++)mx=max(mx,v[k].get(x));
                ans=min(ans,ll(x+ceil(mx)));
            }
        }
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}