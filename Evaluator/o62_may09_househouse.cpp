#include<bits/stdc++.h>
#include "househouse.h"

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int c,m;
    househouse_init(c,m);
    if(2*c>=m){
        househouse_pay(c);
    }
    int n=c/2;
    for(int i=0;i<n;++i)househouse_pay(1);
    househouse_pay(c);
}