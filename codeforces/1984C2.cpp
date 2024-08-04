#include"template/Header.hpp"
#include"modular-arithmetic/MontgomeryModInt.hpp"

using P = pair<ll,mint>;

void runcase(){
    int n;
    cin >> n;
    P l(0,1),r(0,1);
    bool ok=false;
    while(n--){
        ll x;
        cin >> x;
        if(!ok){
            if(l.first+x>=0){
                l.first+=x;
                r.first+=x;
                l.second*=2;
                r.second*=2;
            }else{
                ok=true;
                r.first=abs(r.first+x);
                l.first+=x;
            }
        }else{
            P r1(r.first+x,r.second);
            P r2(l.first+x,l.second);
            P r3(abs(r.first+x),r.second);
            P r4(abs(l.first+x),l.second);
            r=r1;
            if(r.first<r2.first)r=r2;
            else if(r.first==r2.first)r.second+=r2.second;
            if(r.first<r3.first)r=r3;
            else if(r.first==r3.first)r.second+=r3.second;
            if(r.first<r4.first)r=r4;
            else if(r.first==r4.first)r.second+=r4.second;
            l.first+=x;
            if(l.first>=0)l.second*=2;
        }
    }
    cout << r.second << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}