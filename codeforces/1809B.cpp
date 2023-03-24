#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n;
    cin >> n;
    long long l=0,r=1e9;
    while(l<r){
        long long m=(l+r)/2;
        if(m*m>=n)r=m;
        else l=m+1;
    }
    cout << l-1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}