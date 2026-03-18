#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = complex<ll>;

ll cross(P a,P b){
    return imag(conj(a)*b);
}

ll cross(P a,P b,P o){
    return cross(a-o,b-o);
}

ll dot(P a,P b){
    return real(conj(a)*b);
}

ll dot(P a,P b,P o){
    return dot(a-o,b-o);
}

ll sgn(ll x){
    if(x<0)return -1;
    if(x>0)return 1;
    return 0;
}

bool onsegment(P a,P b,P p){
    return cross(a,b,p)==0&&dot(a,p,b)>=0&&dot(b,p,a)>=0;
}

P get(){
    ll x,y;
    cin >> x >> y;
    return P(x,y);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll xl,yl,xr,yr;
        cin >> xl >> yl >> xr >> yr;
        vector<P> a;
        a.push_back(P(xl,yl));
        a.push_back(P(xl,yr));
        a.push_back(P(xr,yr));
        a.push_back(P(xr,yl));
        a.push_back(P(xl,yl));
        P u=get(),v=get();
        auto check=[&](P x){
            for(int i=0;i<4;i++){
                P p=a[i],q=a[i+1];
                if(cross(q,x,p)>=0){
                    return false;
                }
            }
            return true;
        };
        bool ok=check(u)||check(v);
        for(int i=0;i<4;i++){
            P p=a[i],q=a[i+1];
            if(sgn(cross(p,u,v))*sgn(cross(q,u,v))<0&&sgn(cross(u,p,q))*sgn(cross(v,p,q))<0){
                ok=true;
                break;
            }
            if(onsegment(u,v,p)||onsegment(u,v,q)||onsegment(p,q,u)||onsegment(p,q,v)){
                ok=true;
                break;
            }
        }
        cout << (ok?"STOP":"OK") << "\n";
    }
}