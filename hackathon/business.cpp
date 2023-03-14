#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ld a,b,c,d,e,f,g;
    cin >> a >> b >> c >> d >> e >> f >> g;
    ld p1,p2;
    if(a*d<=c)p1=(a*e)+((c-a*d)/f*g);
    else p1=c/d*e;
    if(b*f<=c)p2=(b*g)+((c-b*f)/d*e);
    else p2=c/f*g;
    if(p2>=p1){
        if(b*f<=c)cout << fixed << setprecision(4) << (c-b*f)/d << ' ' << b;
        else cout << fixed << setprecision(4) << 0.0000 << ' ' <<  c/f;
    }else{
        if(a*d<=c)cout << fixed << setprecision(4) << a << ' ' << (c-a*d)/f;
        else cout << fixed << setprecision(4) << c/d << ' ' << 0.0000;
    }
}