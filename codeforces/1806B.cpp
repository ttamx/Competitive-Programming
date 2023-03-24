#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int a=0,b=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x==0)a++;
        if(x==1)b++;
    }
    if(a==n)cout << 1 << '\n';
    else if(a<=(n+1)/2)cout << 0 << '\n';
    else if(a+b==n)cout << 2 << '\n';
    else cout << 1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}