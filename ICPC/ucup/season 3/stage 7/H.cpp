#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int x1,y1,z1,p1,q1;
    cin >> x1 >> y1 >> z1 >> p1 >> q1;
    int x2,y2,z2,p2,q2;
    cin >> x2 >> y2 >> z2 >> p2 >> q2;
    if(p1*q2-p2*q1==0){
        int dx=x1-x2,dy=y1-y2;
        if(dx*p1+dy*q1==0&&dx*p2+dy*q2==0){
            cout << 2 << "\n";
        }else{
            cout << 4 << "\n";
        }
    }else{
        int x=(x1+x2)/2,y=(y1+y2)/2,z=(z1+z2)/2;
        cout << 3 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}