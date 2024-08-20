#include<bits/stdc++.h>

using namespace std;

template<class T>
T euclid(T a,T b,T &x,T &y){
    if(b==0)return x=1,y=0,a;
    T g=euclid(b,a%b,y,x);
    return y-=a/b*x,g;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    int sum=0;
    for(auto &x:a){
        cin >> x;
        sum+=x;
        sum%=m;
    }
    long long s,d;
    int g=euclid((long long)n,1LL*n*(n+1)/2,s,d);
    s%=m,d%=m;
    if(s<0)s+=m;
    if(d<0)d+=m;
    if(g%m==0){
        cout << sum << "\n";
        cout << "0 0\n";
        exit(0);
    }
    int t,_;
    int g2=euclid(g,m,t,_);
    t%=m;
    if(t<0)t+=m;
    int dif=m/g2-(sum/g2);
    s=s*t%m*dif%m;
    d=d*t%m*dif%m;
    cout << sum%g2 << "\n";
    cout << s << " " << d << "\n";
}