#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a[2][2];
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)cin >> a[i][j];
    auto check=[&](double m){
        double l[2][2],r[2][2];
        for(int i=0;i<2;i++)for(int j=0;j<2;j++){
            l[i][j]=a[i][j]-m;
            r[i][j]=a[i][j]+m;
        }
        double mn[2],mx[2];
        for(int i=0;i<2;i++){
            mn[i]=min({l[0][i]*l[1][i^1],l[0][i]*r[1][i^1],r[0][i]*l[1][i^1],r[0][i]*r[1][i^1]});
            mx[i]=max({l[0][i]*l[1][i^1],l[0][i]*r[1][i^1],r[0][i]*l[1][i^1],r[0][i]*r[1][i^1]});
        }
        return max(mn[0],mn[1])<=min(mx[0],mx[1]);
    };
    double l=0,r=1e9;
    for(int t=0;t<10000;t++){
        double m=(l+r)/2;
        if(check(m))r=m;
        else l=m;
    }
    cout << fixed << setprecision(10) << (l+r)/2 << "\n";
}