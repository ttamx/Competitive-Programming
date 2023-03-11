#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int num=3;
    int a[2]={};
    int x=0;
    while(n>=num){
        n-=num;
        a[x]+=num/2;
        a[x^1]+=num/2+1;
        x^=1;
        num+=4;
    }
    if(n>=num/2){
        a[x]+=num/2;
        n-=num/2;
    }else{
        a[x]+=n;
        n=0;
    }
    a[x^1]+=n;
    cout << a[0] << ' ' << a[1] << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}