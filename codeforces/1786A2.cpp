#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int num=3;
    int a[2][2]={};
    int x=0,c=0;
    while(n>=num){
        n-=num;
        a[x][c]+=num/2/2+1;
        a[x][c^1]+=num/2/2;
        a[x^1][c^1]+=(num/2+1)/2;
        a[x^1][c]+=(num/2+1)/2;
        x^=1;
        c^=1;
        num+=4;
    }
    if(n>=num/2){
        a[x][c]+=num/2/2+((num/2)&1);
        a[x][c^1]+=num/2/2;
        n-=num/2;
    }else{
        a[x][c]+=n/2+(n&1);
        a[x][c^1]+=n/2;
        n=0;
    }
    a[x^1][c]+=n/2;
    a[x^1][c^1]+=n/2+(n&1);
    cout << a[0][0] << ' ' << a[0][1] << ' ' << a[1][0] << ' ' << a[1][1] << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}