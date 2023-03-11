#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int mn=1,mx=1;
    int l=0,r=n-1;
    for(int i=0;i<n;i++){
        if(s[i]=='1')mn+=1<<l,l++;
    }
    r=n-1;
    for(int i=0;i<n;i++){
        if(s[i]=='1')mx+=(1<<r),r--;
    }
    for(int i=mn;i<=mx;i++)cout << i << ' ';
}