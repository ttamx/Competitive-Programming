#include <bits/stdc++.h>
using namespace std;

using db=double;
const db pi=acos(-1.0),k=1e-7;

db u,r,d,a,b,x,y,sum;

db f (db nx){
    return sqrt(b*b-b*b*nx*nx/(a*a));
}

int main (){
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        cin >> u >> r >> d;
        b=2.0*r;
        a=(4.0*r+u*(pi*8.0*r/(8.0*u-pi*u)))/2.0;
        x=sqrt(a*a/2 + d/2);
        y=sqrt(b*b-b*b*x*x/(a*a));
        sum=sqrt(y*y+(d-x)*(d-x));
        db t=pi*8.0*r/(8*u-pi*u);
        db s1=2*u*t;
        db s2=pi*(2.0*a+2.0*b)/4.0;
        cout << " => " << t << ' ' << s1 << ' ' << s2 << '\n';
        db m1=(-b*b/a/a*2.0*x)/2.0/sqrt(b*b-b*b*x*x/a/a);
        db m2=sqrt(b*b-b*b*x*x/a/a)*-1.0/(d-x);
        // while (abs(m1-m2)>k){
        //     if (m1>m2) x+=k;
        //     else x-=k;
        //     m1=(-b*b/a/a*2.0*x)/2.0/sqrt(b*b-b*b*x*x/a/a);
        //     m2=sqrt(b*b-b*b*x*x/a/a)*-1.0/(d-x);
        //     y=sqrt(b*b-b*b*x*x/(a*a));
        //     sum=sqrt(y*y+(d-x)*(d-x));
        // }
        cout << a << ' ' << b <<  ' ' << x << ' ' << y << ' ' << d << ' ' << sum << ' ' << m1 << ' ' << m2 << '\n';
        db tmp=x*x/a/a+y*y/b/b;
        cout << "=>" << tmp << '\n';
        if (b>=d){
            cout << "!" << d/(2.0*u) << '\n';
            continue;
        }
        for (db i=k;i<=x;i+=k){
            db dy = f(i)-f(i-k);
            sum+=sqrt(k*k+dy*dy);
        }
        cout << setprecision(12) << sum/(2.0*u) << '\n'; 
    }
    
}