#include<bits/stdc++.h>

using namespace std;

void runcase(){
    double px,py,ax,ay,bx,by;
    cin >> px >> py >> ax >> ay >> bx >> by;
    auto pw=[&](double x){
        return x*x;
    };
    double ans=1e18;
    ans=min(ans,max(pw(ax)+pw(ay),pw(ax-px)+pw(ay-py)));
    ans=min(ans,max(pw(bx)+pw(by),pw(bx-px)+pw(by-py)));
    double d=(pw(ax-bx)+pw(ay-by))/4;
    ans=min(ans,max({d,pw(ax)+pw(ay),pw(bx-px)+pw(by-py)}));
    ans=min(ans,max({d,pw(bx)+pw(by),pw(ax-px)+pw(ay-py)}));
    cout << fixed << setprecision(20) << sqrt(ans) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}