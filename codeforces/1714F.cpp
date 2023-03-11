#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,a,b,c;
    cin >> n >> a >> b >> c;
    if((a+b+c)&1){
        cout << "NO\n";
        return;
    }
    int x=(a+b+c)/2-b,y=(a+b+c)/2-c,z=(a+b+c)/2-a;
    if(x+y+z>n-1||x<0||y<0||z<0||(y==0&&z==0)){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    int cnt=4,p=1;
    bool ok2=true,ok3=true;
    for(int i=1;i<x;i++){
        cout << p << ' ' << cnt << '\n';
        p=cnt++;
    }
    if(y==0){
        cout << p << ' ' << 2 << '\n';
        p=2;
        ok2=false;
    }else if(z==0){
        cout << p << ' ' << 3 << '\n';
        p=3;
        ok3=false;
    }else if(x>0){
        cout << p << ' ' << cnt << '\n';
        p=cnt++;
    }
    int f=p;
    for(int i=1;i<y;i++){
        cout << p << ' ' << cnt << '\n';
        p=cnt++;
    }
    if(ok2)cout << p << ' ' << 2 << '\n';
    p=f;
    for(int i=1;i<z;i++){
        cout << p << ' ' << cnt << '\n';
        p=cnt++;
    }
    if(ok3)cout << p << ' ' << 3 << '\n';
    while(cnt<=n){
        cout << p << ' ' << cnt << '\n';
        p=cnt++;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}