#include<bits/stdc++.h>

using namespace std;

const int LIM=100;

int rnd(int x){
    return rand()%x;
}

int rnd(int l,int r){
    return l+rnd(r-l+1);
}

int main(int argc,char *argv[]){
    cin.tie(nullptr)->sync_with_stdio(false);
    srand(stoi(argv[1]));
    for(int i=0;i<10;i++)rand();
    int n=100;
    int m=rnd(3,n);
    cout << n << " " << m << "\n";
    for(int i=1;i<=n;i++)cout << rnd(1,1000) << " " << rnd(1,1000) << "\n";
}