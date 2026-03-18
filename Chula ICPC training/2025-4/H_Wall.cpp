#include<iostream>
#include<complex>
#include<algorithm>
#include<vector>

using namespace std;

using ll = long long;
using P = complex<ll>;

ll cross(P a,P b){
    return imag(conj(a)*b);
}

ll cross(P a,P b,P o){
    return cross(a-o,b-o);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,rad;
    cin >> n >> rad;
    vector<P> a(n);
    for(auto &e:a){
        ll x,y;
        cin >> x >> y;
        e=P(x,y);
    }
    sort(a.begin(),a.end(),[&](P x,P y){
        return real(x)<real(y)||(real(x)==real(y)&&imag(x)<imag(y));
    });
    vector<P> hull;
    for(int t=0;t<2;t++){
        int sz=hull.size();
        for(auto e:a){
            while(hull.size()>=sz+2&&cross(hull.back(),e,hull.end()[-2])<=0){
                hull.pop_back();
            }
            hull.emplace_back(e);
        }
        hull.pop_back();
        reverse(a.begin(),a.end());
    }
    double ans=0;
    for(int i=0;i<hull.size();i++){
        ans+=sqrtl(norm(hull[i]-hull[(i+1)%hull.size()]));
    }
    cout << ll(ans+acos(-1.0)*2*rad+.5) << "\n";
}