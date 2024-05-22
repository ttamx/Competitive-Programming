#include<bits/stdc++.h>

using namespace std;

int main(){
    int t=1,n=2e5,k=n/3;
    cout << t << "\n";
    cout << n << " " << 1 << " " << n << "\n";
    for(int i=0;i<k;i++)cout << 'a';
    for(int i=2*k;i<n;i++)cout << char('a'+rand()%26);
    for(int i=0;i<k;i++)cout << 'a';
}