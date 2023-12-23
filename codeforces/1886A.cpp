#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n<7||n==9)return void(cout << "NO\n");
    cout << "YES\n";
    if(n%3==0){
        cout << 1 << " " << 4 << " " << n-5 << "\n";
    }else{
        cout << 1 << " " << 2 << " " << n-3 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}