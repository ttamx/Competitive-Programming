#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;

const db PI = acos(-db(1));

template<class T>
using P = complex<T>;

template<class T>
T dot(P<T> a,P<T> b,P<T> o=P<T>(0)){
    a-=o,b-=o;
    return real(conj(a)*b);
}

template<class T>
T cross(P<T> a,P<T> b,P<T> o=P<T>(0)){
    a-=o,b-=o;
    return imag(conj(a)*b);
}

pair<P<db>,P<db>> circle_line(double r,P<db> a,P<db> b){
    P<db> c(0,0);
    P<db> ab=b-a,p=a+ab*dot(c-a,ab)/norm(ab);
    db s=cross(b,c,a),h2=r*r-s*s/norm(ab);
    assert(h2>0);
    P<db> h=ab/abs(ab)*sqrt(h2);
    return {p-h,p+h};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,rad;
    cin >> n >> rad;
    cout << fixed << setprecision(12);
    if(n==1){
        cout << PI*rad*rad/2.0 << "\n";
        exit(0);
    }
    vector<P<ll>> a;
    for(int i=0;i<n;i++){
        ll x,y;
        cin >> x >> y;
        a.emplace_back(P<ll>(x,y));
    }
    a.emplace_back(0);
    sort(a.begin(),a.end(),[&](P<ll> l,P<ll> r){
        return l.real()<r.real()||(l.real()==r.real()&&l.imag()<r.imag());
    });
    vector<P<ll>> hull;
    for(int t=0;t<2;t++){
        int sz=hull.size();
        for(auto p:a){
            while(hull.size()>=sz+2&&cross(hull.back(),p,hull.end()[-2])<=0){
                hull.pop_back();
            }
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(a.begin(),a.end());
    }
    db ans=0;
    hull.emplace_back(hull[0]);
    for(int i=0;i+1<hull.size();i++){
        auto [p,q]=circle_line(rad,P<db>(hull[i].real(),hull[i].imag()),P<db>(hull[i+1].real(),hull[i+1].imag()));
        db theta=abs(arg(p)-arg(q));
        if(theta>=PI){
            theta=2.0*PI-theta;
        }
        db area=theta*rad*rad;
        area-=abs(cross(p,q));
        ans=max(ans,area);
    }
    cout << ans/2.0 << "\n";
}