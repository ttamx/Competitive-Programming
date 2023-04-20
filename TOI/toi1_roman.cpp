#include<bits/stdc++.h>

using namespace std;

int n;
int a[5];

void calc(int x){
    a[4]+=x/100;
    x%=100;
    if(x>=90){
        a[4]++;
        a[2]++;
    }else if(x>=50){
        a[3]++;
        a[2]+=(x-50)/10;
    }else if(x>=40){
        a[3]++;
        a[2]++;
    }else{
        a[2]+=x/10;
    }
    x%=10;
    if(x>=9){
        a[2]++;
        a[0]++;
    }else if(x>=5){
        a[1]++;
        a[0]+=(x-5);
    }else if(x>=4){
        a[1]++;
        a[0]++;
    }else{
        a[0]+=x;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    while(n)calc(n--);
    for(int i=0;i<5;i++)cout << a[i] << ' ';
}