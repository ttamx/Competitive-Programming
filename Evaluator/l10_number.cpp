#include<bits/stdc++.h>

using namespace std;

int n;
int a[10];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int mn=2e9;
    for(int i=1;i<=9;++i){
        cin >> a[i];
        mn=min(mn,a[i]);
    }
    int digit=n/mn;
    for(int i=9;i>0;--i){
        while(digit&&n-a[i]>=(digit-1)*mn){
            cout << i;
            n-=a[i];
            digit--;
        }
    }
}