#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n&1){
        for(int i=0;i<n;i++)cout << 1 << ' ';
        cout << '\n';
    }else{
        for(int i=2;i<n;i++)cout << 2 << ' ';
        cout << 1 << ' ' << 3 << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}