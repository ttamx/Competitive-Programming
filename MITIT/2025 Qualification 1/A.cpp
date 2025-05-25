#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n%2==0){
        cout << 2025;
        for(int i=0;i<n-4;i++)cout << 0;
        cout << "\n";
    }else{
        cout << 42025;
        for(int i=0;i<n-5;i++)cout << 0;
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}