#include<bits/stdc++.h>

using namespace std;

using db = double;

const db P=2.0/(1+sqrt(5.0));
const db EPS=1e-7;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    db h,rad,da,dw;
    cin >> h >> rad >> da >> dw;
    db l=0,r=h;
    auto f=[&](db x){
        db p1=x/2;
        db p2=h-(h-x)/2;
        db w1=x*dw;
        db w2=(h-x)*da;
        return (p1*w1+p2*w2)/(w1+w2);
    };
    while(r-l>EPS){
        db d=(r-l)*P;
        db ml=r-d;
        db mr=l+d;
        if(f(ml)>f(mr)){
            l=ml;
        }else{
            r=mr;
        }
    }
    cout << fixed << setprecision(12) << l << "\n";
}