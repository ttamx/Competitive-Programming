#include<bits/stdc++.h>

using namespace std;

typedef double db;

const int N=105;
const db PI=acos(-1.0);

int n;
db r;
db x[N],y[N],z[N];
db ans;

db calc(int i,int j){
    j%=n;
    db dx=x[i]-x[j],dy=y[i]-y[j],dz=z[i]-z[j];
    return sqrt(dx*dx+dy*dy+dz*dz);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> r;
    for(int i=0;i<n;i++)cin >> x[i] >> y[i] >> z[i];
    ans=4.0*PI/3.0*r*r*r*n;
    for(int i=0;i<n;i++){
        db d=calc(i,i+1);
        if(d<2*r)ans-=2.0*PI/3.0*(r-d/2)*(r-d/2)*(2*r+d/2);
    }
    cout << fixed << setprecision(12) << ans << "\n";
}